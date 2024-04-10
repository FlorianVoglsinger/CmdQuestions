#include <gtest/gtest.h>
#include <string>
#include <sstream>

#include "DataRecorder.hpp"

#define CHARS_400 "qwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiopqwertzuiop"

TEST(QuestionTest, QuestionTooLong)
{
    DataRecorder rec;

    std::stringstream captured_output;
    std::streambuf* orignal_cout_buf = std::cout.rdbuf();
    std::cout.rdbuf(captured_output.rdbuf());

    //imput 400 chars
    std::string input(CHARS_400);
    input += "? \"answer\""; 
    rec.Save(
        input
    );

    std::cout.rdbuf(orignal_cout_buf);

    EXPECT_TRUE(rec.size() == 0);
    EXPECT_EQ(captured_output.str(),
        std::string("Question \"" + std::string(CHARS_400) + "\" is too long. Max length: 255\n")
    );
}

TEST(QuestionTest, AnswerTooLong)
{
    DataRecorder rec;

    //imput 400 chars
    std::string input("Question");
    input += "? \"answer\" \"answer2\" \"";
    input += CHARS_400;
    input += '\"';
    rec.Save(
       input 
    );

    EXPECT_TRUE(rec.size() == 1);
    EXPECT_TRUE(rec.NrOfAnswers(0) == 2);
}

TEST(QuestionTest, CorrectQuestion)
{
    DataRecorder rec;

    //imput 400 chars
    std::string input("Question? \"answer\" \"answer2\"");
    rec.Save(
       input 
    );

    input = "Question2? \"answer3\" \"answer4\" \"answer5\"";
    rec.Save(
       input 
    );

    EXPECT_TRUE(rec.size() == 2);
    EXPECT_TRUE(rec.NrOfAnswers(0) == 2);
    EXPECT_TRUE(rec.NrOfAnswers(1) == 3);
}

TEST(QuestionTest, Print)
{
    DataRecorder rec;

    //imput 400 chars
    std::string input("Question? \"answer\" \"answer2\"");
    rec.Save(
       input 
    );

    input = "Question2? \"answer3\" \"answer4\" \"answer5\"";
    rec.Save(
       input 
    );

    std::stringstream captured_output;
    std::streambuf* orignal_cout_buf = std::cout.rdbuf();
    std::cout.rdbuf(captured_output.rdbuf());

    rec.Print("Question?");

    std::cout.rdbuf(orignal_cout_buf);

    EXPECT_TRUE(rec.size() == 2);
    EXPECT_EQ(captured_output.str(),
        " > answer\n > answer2\n"
    );
}

TEST(QuestionTest, PrintDefault)
{
    DataRecorder rec;

    //imput 400 chars
    std::string input("Question? \"answer\" \"answer2\"");
    rec.Save(
       input 
    );

    input = "Question2? \"answer3\" \"answer4\" \"answer5\"";
    rec.Save(
       input 
    );

    std::stringstream captured_output;
    std::streambuf* orignal_cout_buf = std::cout.rdbuf();
    std::cout.rdbuf(captured_output.rdbuf());

    rec.Print("Question3?");

    std::cout.rdbuf(orignal_cout_buf);

    EXPECT_TRUE(rec.size() == 2);
    EXPECT_EQ(captured_output.str(),
        " > the answer to life, universe and everything is 42\n"
    );
}