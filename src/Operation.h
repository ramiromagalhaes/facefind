/*
 * Operation.h
 *
 *  Created on: 07/09/2012
 *      Author: ramiro
 */

#ifndef OPERATION_H_
#define OPERATION_H_

#include "ProgramParameters.h"
#include "FaceClassifier.h"
#include "ImageDatabase.h"

class Operation {
public:
	Operation(ProgramParameters params);
	virtual ~Operation();
	virtual void execute() const = 0;

protected:
	ProgramParameters params;
};

class SingleImageEval : public Operation {
public:
	SingleImageEval(ProgramParameters params);
	virtual void execute() const;
};

class InitializeDatabase : public Operation {
public:
	InitializeDatabase(ProgramParameters params);
	virtual void execute() const;
};

class SearchDatabase : public Operation {
public:
	SearchDatabase(ProgramParameters params);
	virtual void execute() const;
};

#endif /* OPERATION_H_ */
