#include "huffman.h"
#include <map>


HuffmanNode* HuffmanNode::buildFromWeights(const Vector<int>& wordWeights) {
	auto comp = [](const HuffmanNode* a, const HuffmanNode* b) { return a->weight() > b->weight(); };
	std::priority_queue<HuffmanNode*, Vector<HuffmanNode*>, decltype(comp)> heap(comp);

	for (int i = 0; i < wordWeights.size(); i++) {
		if (wordWeights[i] <= 0) {
			continue;
		}

		heap.push(new HuffmanNode(i, wordWeights[i]));
	}

	heap.push(new HuffmanNode(SpecialNodeType::EofNode));
	heap.push(new HuffmanNode(SpecialNodeType::StopNode));

	while (heap.size() > 1) {
		HuffmanNode* a = heap.top();
		heap.pop();
		HuffmanNode* b = heap.top();
		heap.pop();
		HuffmanNode* node = new HuffmanNode(b, a);
		heap.push(node);
	}

	HuffmanNode* ret = heap.top();
	heap.pop();

	return ret;
}



void HuffmanNode::_wordToEncoding(const HuffmanNode* node, Vector<unsigned int>& res, int depth, int currEncoding) {
	if (node == nullptr) {
		return;
	}

	if (node->isLeaf()) {
		if (node->isEof()) {
			res[res.size() - 2] = TO_ENCODING(depth, currEncoding);
		}
		else if (node->isStop()) {
			res[res.size() - 1] = TO_ENCODING(depth, currEncoding);
		}
		else {
			res[node->word()] = TO_ENCODING(depth, currEncoding);
		}
	}
	else {
		_wordToEncoding(node->leftChild(), res, depth + 1, currEncoding);
		_wordToEncoding(node->rightChild(), res, depth + 1, currEncoding | (0x1 << depth));
	}
}

void printBinary(char ch) {
	for (int i = 0; i < 8; i++) {
		if (ch & (0x1 << i)) {
			std::cout << '1';
		}
		else {
			std::cout << '0';
		}
	}
}

void printEncoding(unsigned int encoding) {
	int n = BITS_NUM(encoding);
	int bits = ENCODING_TO_BITS(encoding);
	for (int i = 0; i < n; i++) {
		if (bits & (1 << i)) {
			std::cout << '1';
		}
		else {
			std::cout << '0';
		}
	}
	std::cout << std::endl;
}
