#include "encoder.h"

void HuffmanEncoder::_addToBuffer(EncodingType encoding) {
	if (_pos >= BUFFER_SIZE - 5) {
		flush();
	}

	int bits = ENCODING_TO_BITS(encoding);
	int n = BITS_NUM(encoding);
	while (n > 0) {
		if (_nbit + n >= BITS_PER_BYTE) {
			_buf[_pos] |= (bits << _nbit);
			bits >>= (BITS_PER_BYTE - _nbit);
			n -= (BITS_PER_BYTE - _nbit);
			//printBinary(_buf[_pos]);
			_buf[++_pos] = 0;
			_nbit = 0;
		}
		else {
			_buf[_pos] |= (bits << _nbit);
			_nbit += n;
			break;
		}
	}
}

void HuffmanEncoder::_initHeader() {
	_writer->write(1);
	char* words = new char[_wordCounts.size()];
	int* counts = new int[_wordCounts.size()];
	int tot = 0;

	for (int i = 0; i < _wordCounts.size(); i++) {
		if (_wordCounts[i] <= 0) {
			continue;
		}
		words[tot] = (char)i;
		counts[tot] = _wordCounts[i];
		tot++;
	}

	_writer->write(tot);
	_writer->write(words, tot);
	_writer->write((char*)counts, tot * 4);

	delete[] words;
	delete[] counts;
}
