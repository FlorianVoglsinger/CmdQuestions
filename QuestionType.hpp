#ifndef QUESTION_TYPE__HPP
#define QUESTION_TYPE__HPP

#include <vector>
#include <iostream>

// Storage DataType
struct QuestionDataType
{
    std::string mQuestion;
    std::vector<std::string> mAnswers;
};
using QuestionsListType = std::vector<QuestionDataType>;

#endif