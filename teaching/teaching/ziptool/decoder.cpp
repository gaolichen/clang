#include "decoder.h"

bool DefaultDecodeWriter::next() {
	if (!_writingFile) {
		_writingFile = true;
		String s(_structure.data(), _structure.size());
		StorageNode* node = StorageNode::fromString(s);
		Vector<String> paths = directoryPaths(node);

		fs::path root(_path);
		for (int i = 0; i < paths.size(); i++) {
			fs::create_directories(root / paths[i]);
		}

		_files = filePaths(node);
		_fileIndex = -1;
	}

	close();

	if (++_fileIndex >= _files.size()) {
		return false;
	}
	else {
		std::cout << "Extracting " << _files[_fileIndex] << std::endl;
		_out.open(fs::path(_path) / _files[_fileIndex], std::ofstream::binary);
		return true;
	}
}

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

