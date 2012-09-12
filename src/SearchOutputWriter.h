#ifndef SEARCHOUTPUTWRITER_H
#define SEARCHOUTPUTWRITER_H

#include <iostream>
#include <list>

#include "FaceClassifier.h"

using namespace std;

class SearchOutputWriter
{
    public:
        SearchOutputWriter();
        void writeOutput(list<FaceData> &faces);

};

#endif // SEARCHOUTPUTWRITER_H
