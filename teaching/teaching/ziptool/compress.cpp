#include "compress.h"

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
