#pragma once
#include "storage.h"
#include "encoder.h"
#include "decoder.h"

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

class DefaultDecodeWriter : public DecodeWriter {
    String _path;
    Vector<char> _structure;
    bool _writingFile = false;
    Vector<String> _files;
    int _fileIndex = -1;
    std::ofstream _out;

public:
    DefaultDecodeWriter(const String& path) : _path(path) {
    }

    ~DefaultDecodeWriter() {
        close();
    }

    virtual bool next();

    virtual void write(char* bytes, int size) {
        if (!_writingFile) {
            _structure.insert(_structure.end(), bytes, bytes + size);
            //String s(_structure.begin(), _structure.end());
            //std::cout << "_structure = " << s << std::endl;
        }
        else {
            _out.write(bytes, size);
        }
    }

    void close() {
        if (_out.is_open()) {
            _out.close();
        }
    }
};


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