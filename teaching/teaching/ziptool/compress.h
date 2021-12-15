#pragma once
#include "storage.h"
#include "encoder.h"
#include "decoder.h"

class Compresser {
public:
	void compress(const String& sourcePath, const String& destPath) {
		DirectoryReader reader(sourcePath);
        DefaultEncoderWriter writer(destPath);
        HuffmanEncoder encoder(reader.wordCounts(), &writer);

        String s = reader.directoryTree();
        for (int i = 0; i < s.length(); i++) {
            encoder.append(CHAR_TO_INT(s[i]));
        }

        while (reader.nextFile()) {
            std::cout << "compressing " << reader.currentFile() << std::endl;
            encoder.split();
            char buf[BUFFER_SIZE];
            int cnt;
            while (cnt = reader.readFile(buf, BUFFER_SIZE)) {
                for (int i = 0; i < cnt; i++) {
                    encoder.append(CHAR_TO_INT(buf[i]));
                }
            }
        }
        encoder.close();
	}

    void extract(const String& file, const String& destPath) {
        CompressedFileReader reader(file);
        DefaultDecodeWriter writer(destPath);
        HuffmanDecoder decoder(reader.wordCounts(), &writer);
        
        char buf[BUFFER_SIZE];
        int cnt;
        while (cnt = reader.read(buf, BUFFER_SIZE)) {
            for (int i = 0; i < cnt; i++) {
                decoder.append(CHAR_TO_INT(buf[i]));
            }
        }
        reader.close();
        decoder.close();
    }
};