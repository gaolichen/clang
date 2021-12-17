#include "decoder.h"

void HuffmanDecoder::append(char encoding) {
	for (int i = 0; i < 8; i++) {
		if (_currentNode->isLeaf()) {
			_currentNode = _tree;
		}

		if (encoding & (0x1 << i)) {
			_currentNode = _currentNode->rightChild();
		}
		else {
			_currentNode = _currentNode->leftChild();
		}

		if (_currentNode->isStop()) {
			close();
			return;
		}
		else if (_currentNode->isEof()) {
			flush();
			_writer->next();
		}
		else if (_currentNode->isLeaf()) {
			_addToBuffer(_currentNode->word());
		}
	}
}

