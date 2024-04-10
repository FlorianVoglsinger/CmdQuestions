#include <iostream>

#include "DataRecorder.hpp"

//--------------------------------------------------
void DataRecorder::Save(const std::string& crInput)
{
    std::stringstream ss;
    QuestionDataType question;

    std::string buffer;
    ss << crInput;
    std::getline(ss, buffer, '?');

    if (!CheckQuestionSize(buffer))
        return;

    question.mQuestion = buffer + "?";

    while (std::getline(ss, buffer, '"') && std::getline(ss, buffer, '"'))
    {        
        if (buffer.size() > MAX_ANSWER_SIZE)
        {
            std::cout << "Answer \"" << buffer << "\" is too long. Max length: " << std::to_string(MAX_ANSWER_SIZE) << std::endl;            
            continue;
        }
        question.mAnswers.push_back(buffer);
    }
    std::cout << std::flush;

    if(question.mAnswers.size() == 0)
    {
        std::cout << "A question needs atleast an answer." << std::endl;
        return;
    }

    mQuestions.push_back(question);
    std::cout << "Question saved!" << "\n" <<
        question.mQuestion << "\n";
    for (const auto& entry : question.mAnswers)
    {
        std::cout << " > " << entry << "\n";
    }
    std::cout << std::flush;
}

//--------------------------------------------------
void DataRecorder::Print(const std::string& crInput)
{
    std::stringstream ss;
    QuestionDataType question;
    std::string buffer;
    ss << crInput;
    std::getline(ss, buffer, '?');

    if (!CheckQuestionSize(buffer))
        return;

    buffer += '?';

    auto it_answers = FindAnswers(buffer);
    if (mQuestions.cend() != it_answers)
    {
        for (const auto& entry : it_answers->mAnswers)
        {
            std::cout << " > " << entry << "\n";
        }
        std::cout << std::flush;
    }
    else
    {
        std:: cout << " > the answer to life, universe and everything is 42" << std::endl;
    }
}

//--------------------------------------------------
QuestionsListType::const_iterator DataRecorder::FindAnswers(const std::string& crQuestion) const
{
    for (auto it = mQuestions.cbegin(); it != mQuestions.cend(); ++it)
    {
        if (it->mQuestion == crQuestion)
            return it;
    }
    return mQuestions.cend();
}

//--------------------------------------------------
bool DataRecorder::CheckQuestionSize(const std::string& crQuestion)
{
    if (crQuestion.size() > MAX_QUESTION_SIZE)
    {
        std::cout << "Question \"" << crQuestion << "\" is too long. Max length: " <<
            std::to_string(MAX_QUESTION_SIZE) << std::endl;            
        return false;
    }
    
    return true;
}