#ifndef TEXTGCNdev_H
#define TEXTGCNdev_H

#include "LINE.h"

/*****
 * TEXTGCNdev
 * **************************************************************/

class TEXTGCNdev: public LINE {

    public:

        TEXTGCNdev();
        ~TEXTGCNdev();

        vector< vector<double> > w_context2;

        void SaveWeights(string);

        // additional model parameters
        int num_aggregation = 5;

        // model function
        void Init(int);
        void LoadFieldMeta(string);
        void Train(int, int, int, double, double, int);

};


#endif
