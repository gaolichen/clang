// ziptool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>
#include "storage.h"
#include "huffman.h"
#include "encoder.h"
#include "compress.h"
namespace fs = std::filesystem;

#pragma region Tests

void testStorage() {
    StorageNode* node = StorageNode::fromPath("D:/gitroot/clang/teaching/teaching/ziptool/");
    std::cout << node->toString() << std::endl << std::endl;

    String s = node->toString();
    StorageNode* node2 = StorageNode::fromString(s);

    String s2 = node2->toString();
    std::cout << (s == s2) << std::endl;
    std::cout << s2 << std::endl;

    std::cout << filePaths(node2) << std::endl << std::endl;

    std::cout << directoryPaths(node2) << std::endl;
}

void testDirectoryReader() {
    String path = "D:/gitroot/clang/problems/week1";
    DirectoryReader reader(path);
    std::cout << reader.directoryTree() << std::endl << std::endl;

    while (reader.nextFile()) {
        std::cout << reader.currentFile() << std::endl;
        char buf[100];
        int cnt;
        while (cnt = reader.readFile(buf, 99)) {
            buf[cnt] = 0;
            std::cout << buf << std::endl;
        }
        std::cout << std::endl;
    }
}

void typeTest() {
    char ch = 0xff;
    unsigned int i = ch;
    std::cout << (int)ch << ' ' << (ch & 0xffff) << ' ' << (unsigned int)ch << std::endl;

    char ch2 = 256;
    int j = 0xffffff61;
    char ch3 = j;
    std::cout << 0xffffffff << ' ' << j << ' ' << ch3 << std::endl;
    std::cout << (int)ch2 << ' ' << (int)'a' << std::endl;
}

void testCompress() {
    Compresser comp;
    String path1 = "D:/gitroot/clang/problems/week1";
    String path2 = "D:/gitroot/clang/problems/week1.myzip";
    comp.compress(path1, path2);
}

void testExtract() {
    Compresser comp;
    String path2 = "D:/gitroot/clang/problems/week1.myzip";
    String path1 = "D:/gitroot/clang/problems/week1_new";
    comp.extract(path2, path1);
}

void testCompressFile() {
    String path1 = "D:/gitroot/clang/problems/week1";
    String path2 = "D:/gitroot/clang/problems/week1.myzip";
    CompressedFileReader cf(path2);

    DirectoryReader reader(path1);
    std::cout << cf.wordCounts() << std::endl;
    std::cout << reader.wordCounts() << std::endl;

    cf.close();
}

class TestEncoderWriter : public EncoderWriter {
    Vector<char> _cache;
public:
    virtual void write(const char* bytes, int size) {
        std::cout << "TestEncoderWriter: \n";
        for (int i = 0; i < size; i++) {
            printBinary(bytes[i]);
            _cache.push_back(bytes[i]);
        }

        std::cout << std::endl;
    }

    virtual void write(int x) {
        //_cache.push_back();
    }

    virtual void close() {
        std::cout << "TestEncoderWriter closed()" << std::endl;
        std::reverse(_cache.begin(), _cache.end());
    }

    int read(char* buf, int size) {
        int i;
        for (i = 0; i < size && !_cache.empty(); i++) {
            buf[i] = _cache.back();
            _cache.pop_back();
        }
        return i;
    }
};

class TestDecodeWriter : public DecodeWriter {
public:
    virtual bool next() {
        return true;
    }

    virtual void write(char* bytes, int size) {
        std::cout << "\nTestDecodeWriter::writer()" << std::endl;
        for (int i = 0; i < size; i++) {
            std::cout << bytes[i];
        }

        std::cout << std::endl;
    }

    virtual void close() {
    }
};

void testDecoder() {
    String sourcePath = "D:/gitroot/clang/problems/week1";
    DirectoryReader reader(sourcePath);
    TestEncoderWriter writer;
    Vector<int> wordCounts = reader.wordCounts();
    HuffmanEncoder encoder(wordCounts, &writer);
    HuffmanNode* node = HuffmanNode::buildFromWeights(wordCounts);
    Vector<EncodingType> wordToEncoding = node->wordToEncoding();

    String content = "hello world.";
    String s = content + "*sa4";
    for (int i = 0; i < s.length(); i++) {
        std::cout << s[i] << '\t';
        printEncoding(wordToEncoding[s[i]]);
    }

    for (int i = 0; i < content.length(); i++) {
        encoder.append(content[i]);
    }
    encoder.close();

    char buf[100];
    int cnt = writer.read(buf, 100);

    TestDecodeWriter decodeWriter;
    HuffmanDecoder decoder(wordCounts, &decodeWriter);

    for (int i = 0; i < cnt; i++) {
        decoder.append(buf[i]);
    }
    decoder.close();
}

void runTests() {
    //run();
    //testDirectoryReader();
    //testCompress();
    //testCompressFile();
    //testExtract();
    //testDecoder();
}

#pragma endregion


#pragma region Integrated Test

void createFiles(const String& root, const Vector<String>& dirs, const Vector<String>& files, const Vector<String>& contents) {
    fs::path rootPath(root);
    for (const String& dir : dirs) {
        fs::create_directories(rootPath / dir);
    }

    for (int i = 0; i < files.size(); i++) {
        std::ofstream out(rootPath / files[i]);
        out << contents[i];
        out.close();
    }
}

bool verifyFiles(const String& root, const Vector<String>& dirs, const Vector<String>& files, const Vector<String>& contents) {
    fs::path rootPath(root);
    for (const String& dir : dirs) {
        if (!fs::exists(rootPath / dir)) {
            std::cerr << "Cannot find directory " << rootPath / dir << std::endl;
            return false;
        }
    }

    for (int i = 0; i < files.size(); i++) {
        std::ifstream in(rootPath / files[i]);
        String s, content;
        while (std::getline(in, s)) {
            if (content.length()) {
                content += '\n';
            }
            content += s;
        }
        in.close();

        if (content != contents[i]) {
            std::cerr << "content not match! retruned = " << content << ", expected =" << contents[i] << std::endl;
            return false;
        }
    }

    return true;
}

void integratedTest() {
    String root = "test_root";
    Vector<String> dirs{ "test_folder1", "test_folder1/test_folder2" };
    Vector<String> files{ "test_folder1/test1.txt", "test_folder1/test2.txt", };
    Vector<String> contents{ "Some content for test. ", "Some other content for test." };

    createFiles("./" + root, dirs, files, contents);

    Compresser cmp;
    String dest = "./test.szip";
    cmp.compress(root, dest);

    if (!fs::exists(dest)) {
        std::cerr << "Cannot find file " << dest << std::endl;
        return;
    }

    String dest2 = "./extracted";
    cmp.extract(dest, dest2);

    if (!verifyFiles(dest2 + "/" + root, dirs, files, contents)) {
        return;
    }

    fs::remove_all(fs::path("./" + root));
    fs::remove_all(fs::path(dest2));
    fs::remove_all(fs::path(dest));

    std::cout << "Passed integrated test!!" << std::endl;
}

#pragma endregion

void fibo(int n) {
    EncodingType a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        EncodingType c = a;
        a = b;
        b += c;
        std::cout << i + 1 << ' ' << a << std::endl;
    }
}

void showHelp() {
    std::cout << "szip zip|unzip source [dest]" << std::endl;
}

int main(int argc, char** argv) {
    //runTests();
    //integratedTest();

    if (argc < 3) {
        showHelp();
        return -1;
    }

    String cmd = argv[1];
    if (cmd != "zip" && cmd != "unzip") {
        showHelp();
        return -1;
    }

    String source = argv[2];
    String dest;
    if (argc >= 4) {
        dest = argv[3];
    }

    if (!fs::exists(source)) {
        std::cerr << "The path " << source << " does not exist." << std::endl;
        return -1;
    }
    
    Compresser cmp;
    if (cmd == "zip") {
        if (dest == "") {
            dest = (fs::path("./") / fs::path(source).filename()).string() + ".szip";
        }
        cmp.compress(source, dest);
    }
    else {
        if (dest == "") {
            dest = "./";
        }
        cmp.extract(source, dest);
    }

    return 0;
}
