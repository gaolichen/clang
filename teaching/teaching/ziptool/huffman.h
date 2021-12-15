#pragma once
#include "types.h"
#include <cstdlib>
#include <queue>

#define ENCODING_TO_BITS(x) ((x) & 0x7ffffff)
#define BITS_NUM(x) ((x)>>27)
#define TO_ENCODING(depth, bits) (((depth) << 27) | (bits))

typedef int WordType;
enum SpecialNodeType : int { EofNode = 1, StopNode = 2 };

class HuffmanNode {
protected:
	int _weight = 0;
	WordType _word = 0;
	HuffmanNode* _left = nullptr;
	HuffmanNode* _right = nullptr;

	static void _wordToEncoding(const HuffmanNode* node, Vector<unsigned int>& res, int depth, int encoding);
public:
	HuffmanNode(WordType word, int weight) : _word(word), _weight(weight) {
	}

	HuffmanNode(HuffmanNode* left, HuffmanNode* right) : _left(left), _right(right) {
		_weight = _left->_weight + _right->_weight;
	}

	HuffmanNode(SpecialNodeType type) : _word((WordType)type) {
	}

	~HuffmanNode() {
		if (_left) {
			delete _left;
			_left = nullptr;
		}
		if (_right) {
			delete _right;
			_right = nullptr;
		}
	}

	int weight() const {
		return _weight;
	}

	WordType word() const {
		return _word;
	}

	bool isStop() const {
		return _weight == 0 && _word == StopNode;
	}

	bool isEof() const {
		return _weight == 0 && _word == EofNode;
	}

	bool isLeaf() const {
		return _left == nullptr && _right == nullptr;
	}

	HuffmanNode* leftChild() const {
		return _left;
	}

	HuffmanNode* rightChild() const {
		return _right;
	}

	Vector<unsigned int> wordToEncoding() const {
		Vector<unsigned int> res(256 + 2, 0);
		_wordToEncoding(this, res, 0, 0);
		return res;
	}

	static HuffmanNode* buildFromWeights(const Vector<int>& wordWeights);
};

void printBinary(char ch);
void printEncoding(unsigned int encoding);