#ifndef LINE_H
#define LINE_H

#include "../proNet.h"

/*****
 * LINE
 * **************************************************************/

class LINE {

    public:
        
        LINE();
        ~LINE();
        
        proNet pnet;

        // parameters
        int dim;                // representation dimensions
        int order=2;
        vector< vector<double> > w_vertex_o1;
        vector< vector<double> > w_vertex;
        vector< vector<double> > w_context;
        
        double *w_vertex1, *w_context1;


        // data function
        void LoadEdgeList(string, bool);
        void SaveWeights(string);
        
        // model function
        void Init(int, int);
        void Train(int, int, double, int);

};


#endif
