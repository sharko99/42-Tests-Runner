#include <iostream>
#include <filesystem>
#include <vector>
#include <cstdlib> 

namespace fs = std::filesystem;

int runTest(const std::string &testName, const std::vector<fs::path> &testFiles, const std::string &headerName = "", bool includeAll = false)
{
    int exitCode = 0;
    for (const auto &testFile : testFiles)
    {
        std::string command = "mkdir -p traces && mkdir -p traces/" + testName + " && gcc -o test_executable " + (includeAll ? "*" : testName) + ".c " + testFile.string() + " -lbsd && ./test_executable > traces/" + testName + "/" + testFile.filename().string() + "_trace.txt" + (headerName != "" ? " -DHEADER_NAME=" + headerName : "");
        std::cout << "Running " << testFile.filename().string() << "... ";
        if (std::system(command.c_str()) == 0)
        {
            std::cout << "\033[32mPassed\033[0m\n";
        }
        else
        {
            std::cout << "\033[31mFailed\033[0m\n";
            exitCode = 1;
        }
        std::system("rm -f test_executable");
    }
    return exitCode;
}


int main(int argc, char **argv)
{
    std::vector<std::string> functionsToTest;
    bool includeAll = false;
    bool includeHeader = false;
    std::string headerName = "";

    std::cout << "\033[34m----------------------------------------\n";
    std::cout << "| \033[36m42 Tests Runner\033[34m                      |\n";
    std::cout << "| \033[36mBy: @lbunelle\033[34m                        |\n";
    std::cout << "----------------------------------------\033[0m\n";
    if (argc == 1)
    {
        for (const auto &entry : fs::directory_iterator("tests"))
        {
            if (entry.is_directory())
            {
                functionsToTest.push_back(entry.path().filename().string());
            }
        }
    }
    else
    {
        for (int i = 1; i < argc; ++i)
        {
            if (argv[i][0] == '-')
            {
                if (argv[i][1] == 'd')
                {
                    includeHeader = true;
                    if (i + 1 >= argc)
                    {
                        std::cout << "\033[31mNo header name provided.\033[0m\n";
                        return 1;
                    }
                    headerName = argv[i + 1];
                    i++;
                    std::cout << "\033[33mIncluding header " << headerName << ".\033[0m\n";
                    if (argc - i == 1)
                    {
                        for (const auto &entry : fs::directory_iterator("tests"))
                        {
                            if (entry.is_directory())
                            {
                                functionsToTest.push_back(entry.path().filename().string());
                            }
                        }
                    }
                }
                else if (argv[i][1] == 'a')
                {
                    includeAll = true;
                    std::cout << "\033[33mIncluding all files.\033[0m\n";
                    if (argc - i == 1)
                    {
                        for (const auto &entry : fs::directory_iterator("tests"))
                        {
                            if (entry.is_directory())
                            {
                                functionsToTest.push_back(entry.path().filename().string());
                            }
                        }
                    }
                }
                else
                {
                    std::cout << "\033[31mInvalid argument " << argv[i] << ".\033[0m\n";
                    return 1;
                }
            }
            else
                functionsToTest.push_back(argv[i]);
        }
        std::cout << "\n";
    }

    for (const auto &functionName : functionsToTest)
    {
        fs::path testFolderPath = fs::path("tests") / functionName;
        if (!fs::exists(testFolderPath) || !fs::is_directory(testFolderPath))
        {
            std::cout << "\033[33mTest for " << functionName << " not found or no tests available.\033[0m\n";
            continue;
        }
        std::cout << "\033[36m>> Tests for " << functionName << "\033[0m\n";

        std::vector<fs::path> testFiles;
        for (const auto &testFile : fs::directory_iterator(testFolderPath))
        {
            testFiles.push_back(testFile.path());
        }

        int code = runTest(functionName, testFiles, headerName, includeAll);
        if(code == 0)
        {
            std::cout << "\033[32mAll tests passed for " << functionName << "\033[0m\n\n";
        }
        else
        {
            std::cout << "\033[31mSome tests failed for " << functionName << "\033[0m\n\n";
        }
    }

    return 0;
}
