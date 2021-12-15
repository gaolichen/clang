#include "storage.h"
#include <filesystem>
namespace fs = std::filesystem;

StorageNode* fromString(const String& s, int start, int end) {
	int pos1 = s.find('<', start);
	if (pos1 == String::npos || pos1 >= end) {
		return new FileNode(s.substr(start, end - start));
	}

	if (s[end - 1] != '>') {
		std::cout << "Error: " << s.substr(start, end - start) << std::endl;
		return nullptr;
	}
	String name = s.substr(start, pos1 - start);
	DirectoryNode* node = new DirectoryNode(name);

	int cnt = 0;
	int pos2 = end - 1;
	int pos = pos1 + 1;
	for (int i = pos; i < pos2; i++) {
		if (s[i] == '<') {
			cnt++;
		}
		else if (s[i] == '>') {
			cnt--;
		}
		else if (cnt > 0) {
			continue;
		} else {
			if (s[i] == '|') {
				node->children().push_back(fromString(s, pos, i));
				pos = i + 1;
			}
			else {
				// do nothing.
			}
		}
	}

	if (pos < pos2) {
		node->children().push_back(fromString(s, pos, pos2));
	}

	return node;
}

StorageNode* StorageNode::fromString(const String& s) {
	return ::fromString(s, 0, s.length());
}

StorageNode* fromDirectoryEntry(const fs::directory_entry& entry) {
	String name = entry.path().filename().string();
	if (entry.is_regular_file()) {
		return new FileNode(name);
	}
	else if (entry.is_directory()) {
		DirectoryNode* ret = new DirectoryNode(name);
		for (auto const& dir_entry : fs::directory_iterator{ entry.path() }) {
			ret->children().push_back(fromDirectoryEntry(dir_entry));
		}
		return ret;
	}

	return nullptr;
}

StorageNode* StorageNode::fromPath(const String& path) {
	if (path.length() > 1 && path[path.length() - 1] == '/') {
		fs::directory_entry entry(path.substr(0, path.length() - 1));
		return fromDirectoryEntry(entry);
	}
	else {
		fs::directory_entry entry(path);
		return fromDirectoryEntry(entry);
	}	
}

void filePaths(StorageNode* node, Vector<String>& ret, const String& path) {
	String newPath = path.length() > 0 ? path + '/' + node->name() : node->name();
	FileNode* file = dynamic_cast<FileNode*>(node);
	if (file) {
		ret.push_back(newPath);
	}
	else {
		DirectoryNode* dire = dynamic_cast<DirectoryNode*>(node);
		for (int i = 0; i < dire->children().size(); i++) {
			filePaths(dire->children(i), ret, newPath);
		}
	}
}

Vector<String> filePaths(StorageNode* node) {
	Vector<String> ret;
	::filePaths(node, ret, "");
	return ret;
}

void directoryPaths(StorageNode* node, Vector<String>& ret, const String& path) {
	String newPath = path.length() > 0 ? path + '/' + node->name() : node->name();

	DirectoryNode* dire = dynamic_cast<DirectoryNode*>(node);
	if (dire) {
		ret.push_back(newPath);
		for (int i = 0; i < dire->children().size(); i++) {
			directoryPaths(dire->children(i), ret, newPath);
		}
	}
}

Vector<String> directoryPaths(StorageNode* node) {
	Vector<String> ret;
	::directoryPaths(node, ret, "");
	return ret;
}
