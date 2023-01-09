#pragma once

#include "ITableLineInterpreterHandler.h"
#include "../graphic-content-parsing/PathElement.h"


class TableLineInterpreter {
    public:
        TableLineInterpreter(void);
        TableLineInterpreter(ITableLineInterpreterHandler* inHandler);
        virtual ~TableLineInterpreter(void);


        void SetHandler(ITableLineInterpreterHandler* inHandler);

        // forwarded by external party implementing IGraphicContentInterpreterHandler
        // with only what's relevant to paths
        bool OnPathPainted(const PathElement& inPathElement);

    private:
        ITableLineInterpreterHandler* handler;

        bool OnStrokePathPainted(const PathElement& inPathElement);
        bool OnFillPathPainted(const PathElement& inPathElement);
};