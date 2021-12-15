#pragma once
#include "types.h"
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

class StorageNode {
	String _name;
public:
	StorageNode(const String& name) :_name(name) {
	}

	const String& name() const {
		return _name;
	}

	virtual String toString() const = 0;

	static StorageNode* fromString(const String& s);

	static StorageNode* fromPath(const String& path);
};

class DirectoryNode : public StorageNode {
	Vector<StorageNode*> _children;
public:
	DirectoryNode(const String& name) : StorageNode(name) {
	}

	~DirectoryNode() {
		for (int i = 0; i < _children.size(); i++) {
			delete _children[i];
		}
		_children.clear();
	}

	StorageNode* children(int i) {
		return _children[i];
	}

	Vector<StorageNode*>& children() {
		return _children;
	}

	virtual String toString() const {
		String ret = name() + "<";
		for (int i = 0; i < _children.size(); i++) {
			if (i > 0) {
				ret += "|";
			}
			ret += _children[i]->toString();
		}
		ret += ">";
		return ret;
	}
};

class FileNode : public StorageNode {
public:
	FileNode(const String& fileName) : StorageNode(fileName) {
	}

	virtual String toString() const {
		return name();
	}
};

Vector<String> filePaths(StorageNode* node);
Vector<String> directoryPaths(StorageNode* node);

class DirectoryReader {
	fs::path _parentPath;
	StorageNode* _root = nullptr;
	Vector<String> _files;
	int _currentFile = -1;
	std::ifstream _input;

	void _close() {
		if (_input.is_open()) {
			_input.close();
		}
	}
public:
	DirectoryReader(const String& path) {
		_parentPath = fs::path(path).parent_path();
		_root = StorageNode::fromPath(path);
		_files = filePaths(_root);
		reset();
	}

	~DirectoryReader() {
		_close();

		if (_root) {
			delete _root;
			_root = nullptr;
		}
	}

	void reset() {
		_close();
		_currentFile = -1;
	}

	String directoryTree() const {
		return _root->toString();
	}

	const String& currentFile() const {
		if (_currentFile < 0 || _currentFile >= _files.size()) {
			return "";
		}
		else {
			return _files[_currentFile];
		}
	}

	bool nextFile() {
		_close();

		if (++_currentFile >= _files.size()) {
			return false;
		}

		_input.open(_parentPath / _files[_currentFile], std::ifstream::binary | std::ifstream::in);
		return (_input.rdstate() & std::ifstream::failbit) == 0;
	}

	int readFile(char* buf, int size) {
		if (!_input.is_open()) {
			return 0;
		}

		_input.read(buf, size);
		return _input.gcount();
	}

	Vector<int> wordCounts() {
		Vector<int> ret(256, 0);
		String s = directoryTree();
		for (int i = 0; i < s.length(); i++) {
			ret[CHAR_TO_INT(s[i])]++;
		}

		reset();
		while (nextFile()) {
			char buf[BUFFER_SIZE];
			int cnt;
			while (cnt = readFile(buf, BUFFER_SIZE)) {
				for (int i = 0; i < cnt; i++) {
					ret[CHAR_TO_INT(buf[i])]++;
				}
			}
		}
		reset();

		return ret;
	}
};

class CompressedFileReader {
	String _path;
	std::ifstream _in;
public:
	CompressedFileReader(const String& path) : _path(path) {
		_in.open(path, std::ifstream::binary | std::ifstream::in);
	}

	~CompressedFileReader() {
		if (_in.is_open()) {
			_in.close();
		}
	}

	Vector<int> wordCounts() {
		int n;

		_in.read((char*)(&n), 4);
		_in.read((char*)(&n), 4);

		char* buf = new char[n];
		int* counts = new int[n];

		_in.read(buf, n);
		_in.read((char*)counts, 4 * n);

		Vector<int> ret(256, 0);
		for (int i = 0; i < n; i++) {
			ret[CHAR_TO_INT(buf[i])] = counts[i];
		}

		delete[] buf;
		delete[] counts;

		return ret;
	}

	int read(char* buf, int size) {
		_in.read(buf, size);
		return _in.gcount();
	}

	void close() {
		if (_in.is_open()) {
			_in.close();
		}
	}
};