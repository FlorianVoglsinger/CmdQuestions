#ifndef DATARECORDER__HPP
#define DATARECORDER__HPP

#include <string>
#include <vector>
#include <sstream>

#include "QuestionType.hpp"

// static defines
#define MAX_QUESTION_SIZE 255
#define MAX_ANSWER_SIZE 255

class DataRecorder
{
    public:

    //--------------------------------------------------
    // Save
    // Saves the provided answers and questions.
    // params:  crInput ... user input to be stored
    // return:  
    //--------------------------------------------------
    void Save(const std::string& crInput);

    //--------------------------------------------------
    // Print 
    // Prints the answers to the found question or a default answer if the question is not found.
    // params:  crInput ... user input to be stored
    // return:  
    //--------------------------------------------------
    void Print(const std::string& crInput);

    //--------------------------------------------------
    // FindAnswers
    // Searches for the question string in the stored answers. Returns the found iterator or the end iterator.
    // params:  crInput ... user input to be stored
    // return:  const iterator to the answer
    //--------------------------------------------------
    QuestionsListType::const_iterator FindAnswers(const std::string& crQuestion) const;

    inline size_t NrOfAnswers(const size_t QuestionNr) const
    {
        if (QuestionNr > mQuestions.size())
            return 0;
        return mQuestions[QuestionNr].mAnswers.size();
    }

    inline size_t size() const { return mQuestions.size(); }

    protected:

    private:
    //--------------------------------------------------
    // CheckQuestionSize
    // Checks the provided question string against the MAX_QUESTION_SIZE define. The user is informed incase of
    // an error.
    // params:  crQuestion ... the question string to be checked
    // return:  
    //--------------------------------------------------
    bool CheckQuestionSize(const std::string& crQuestion);

    QuestionsListType mQuestions;    
};

#endif