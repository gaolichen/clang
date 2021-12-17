#pragma once
#include "storage.h"
#include "huffman.h"

class DecodeWriter {
public:
	virtual bool next() = 0;
	virtual void write(char* bytes, int size) = 0;
	virtual void close() = 0;
};

class HuffmanDecoder {
private:
	HuffmanNode* _tree = nullptr;
	HuffmanNode* _currentNode = nullptr;
	DecodeWriter* _writer = nullptr;
	char* _buf = nullptr;
	int _pos = 0;

	void _addToBuffer(char ch) {
		//std::cout << ch << std::endl;
		if (_pos >= BUFFER_SIZE - 5) {
			flush();
		}

		_buf[_pos++] = ch;
	}

public:
	HuffmanDecoder(const Vector<int>& wordWeights, DecodeWriter* writer) : _writer(writer) {
		_tree = HuffmanNode::buildFromWeights(wordWeights);
		_currentNode = _tree;
		_buf = new char[BUFFER_SIZE];
	}

	~HuffmanDecoder() {
		if (_buf) {
			delete[] _buf;
			_buf = nullptr;
		}

		if (_tree) {
			delete _tree;
			_tree = nullptr;
		}
	}

	void flush() {
		_writer->write(_buf, _pos);
		_pos = 0;
	}

	void append(char encoding);

	void close() {
		flush();
		_writer->close();
	}
};
