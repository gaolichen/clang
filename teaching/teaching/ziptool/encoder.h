#pragma once
#include <fstream>
#include "types.h"
#include "storage.h"
#include "huffman.h"

#define BUFFER_SIZE 100
#define BITS_PER_BYTE 8

class EncoderWriter {
public:
	virtual void write(const char* bytes, int size) = 0;
	virtual void write(int x) = 0;
	virtual void close() = 0;
};

class DefaultEncoderWriter : public EncoderWriter {
	String _path;
	std::ofstream _out;
public:
	DefaultEncoderWriter(const String& path) : _path(path) {
		_out.open(path, std::ofstream::out | std::ofstream::binary);
	}

	~DefaultEncoderWriter() {
		close();
	}

	virtual void write(const char* bytes, int size) {
		_out.write(bytes, size);
	}

	virtual void write(int x) {
		_out.write((char*)(&x), 4);
	}

	virtual void close() {
		if (_out.is_open()) {
			_out.close();
		}
	}
};

class HuffmanEncoder {
private:
	HuffmanNode* _tree = nullptr;
	Vector<int> _wordCounts;
	Vector<EncodingType> _word2Encoding;
	char* _buf;
	int _pos = 0;
	int _nbit = 0;
	EncoderWriter* _writer;

	EncodingType _stop;
	EncodingType _splitor;

	void _initHeader();
	void _addToBuffer(EncodingType encoding);
public:
	HuffmanEncoder(const Vector<int>& wordWeights, EncoderWriter* writer) : _wordCounts(wordWeights), _writer(writer) {
		_tree = HuffmanNode::buildFromWeights(wordWeights);
		_word2Encoding = _tree->wordToEncoding();

		_stop = _word2Encoding.back();
		_word2Encoding.pop_back();
		_splitor = _word2Encoding.back();
		_word2Encoding.pop_back();

		_buf = new char[BUFFER_SIZE];
		memset(_buf, 0x0, BUFFER_SIZE);
		_initHeader();
	}

	~HuffmanEncoder() {
		if (_buf != nullptr) {
			delete[] _buf;
			_buf = nullptr;
		}

		if (_tree) {
			delete _tree;
			_tree = nullptr;
		}
	}

	void append(unsigned int value) {
		_addToBuffer(_word2Encoding[value]);
	}

	void split() {
		_addToBuffer(_splitor);
	}

	void close() {
		_addToBuffer(_stop);
		flush(true);
		_writer->close();
	}

	void flush(bool includeLastByte = false) {
		if (includeLastByte && _nbit > 0) {
			_writer->write(_buf, _pos + 1);
			_pos = _nbit = 0;
			_buf[0] = 0;
		}
		else {
			_writer->write(_buf, _pos);
			_buf[0] = _buf[_pos];
			_pos = 0;
		}
	}
};
