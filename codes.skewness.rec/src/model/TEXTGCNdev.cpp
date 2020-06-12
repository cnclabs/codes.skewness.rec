#include "TEXTGCNdev.h"

TEXTGCNdev::TEXTGCNdev() {}
TEXTGCNdev::~TEXTGCNdev() {}

void TEXTGCNdev::SaveWeights(string model_name){

    cout << "Save Model:" << endl;
    ofstream model(model_name);
    if (model)
    {
        int counter = 0;
        for (long vid=0; vid!=pnet.MAX_vid; vid++)
            counter++;
        model << counter << " " << dim << endl;

        int branch;
        float count;
        long temp_vid, temp_vid2;
        double attention_sum;
        vector<double> attention_score;
        vector<double> w_avg;
        w_avg.resize(dim, 0.0);
        for (long vid=0; vid!=pnet.MAX_vid; vid++)
        {
            if (pnet.field[vid].fields[0]==0 || pnet.field[vid].fields[0]==1)
            {
                model << pnet.vertex_hash.keys[vid];
                branch = pnet.vertex[vid].branch;

                for (int b=0; b<branch; b++)
                {
                    temp_vid = pnet.context[pnet.vertex[vid].offset + b].vid;
                    for (int d=0; d<dim; ++d)
                    {
                        w_avg[d] += w_context[temp_vid][d];
                        w_avg[d] += w_vertex[vid][d];
                    }
                }
                for (int d=0; d<dim; ++d)
                {
                    //model << " " << w_avg[d]/(branch*2.0);
                    model << " " << w_avg[d]*5.0/branch;
                    w_avg[d] = 0.0;
                }
                model << endl;
            }
            else
            {
                model << pnet.vertex_hash.keys[vid];
                for (int d=0; d<dim; ++d)
                {
                    model << " " << w_context[vid][d];
                }
                model << endl;
            }
        }
        cout << "\tSave to <" << model_name << ">" << endl;
    }
    else
    {
        cout << "\tfail to open file" << endl;
    }
}

void TEXTGCNdev::Init(int dim) {

    this->dim = dim;
    cout << "Model Setting:" << endl;
    cout << "\tdimension:\t\t" << dim << endl;

    w_vertex.resize(pnet.MAX_vid);
    w_context.resize(pnet.MAX_vid);
    w_context2.resize(pnet.MAX_vid);

    for (long vid=0; vid<pnet.MAX_vid; ++vid)
    {
        w_vertex[vid].resize(dim);
        for (int d=0; d<dim;++d)
        {
            w_vertex[vid][d] = (rand()/(double)RAND_MAX - 0.5) / dim;
        }
    }

    for (long vid=0; vid<pnet.MAX_vid; ++vid)
    {
        w_context[vid].resize(dim);
        w_context2[vid].resize(dim);
        for (int d=0; d<dim;++d)
        {
            w_context[vid][d] = (rand()/(double)RAND_MAX - 0.5) / dim;
            w_context2[vid][d] = (rand()/(double)RAND_MAX - 0.5) / dim;
        }
    }
}

void TEXTGCNdev::LoadFieldMeta(string filename) {
    pnet.LoadFieldMeta(filename);
}

void TEXTGCNdev::Train(int sample_times, int num_events, int num_words, double reg, double alpha, int workers){

    omp_set_num_threads(workers);

    cout << "Model:" << endl;
    cout << "\t[TEXTGCNdev]" << endl;

    cout << "Learning Parameters:" << endl;
    cout << "\tsample_times:\t\t" << sample_times << endl;
    cout << "\tnegative_samples:\t" << "fixed" << endl;
    cout << "\tnum_events:\t" << num_events << endl;
    cout << "\tnum_words:\t" << num_words << endl;
    cout << "\tregularization:\t\t" << reg << endl;
    cout << "\talpha:\t\t\t" << alpha << endl;
    cout << "\tworkers:\t\t" << workers << endl;

    cout << "Start Training:" << endl;

    unsigned long long total_sample_times = (unsigned long long)sample_times*1000000;
    double alpha_min = alpha * 0.0001;
    double alpha_last;

    unsigned long long current_sample = 0;
    unsigned long long jobs = total_sample_times/workers;

    #pragma omp parallel for
    for (int worker=0; worker<workers; ++worker)
    {
        unsigned long long count = 0;
        double _alpha = alpha;
        long user, item;

        while (count<jobs)
        {
            user = pnet.SourceSample();
            while (pnet.field[user].fields[0]!=0)
            //while (pnet.field[user].fields[0]!=0 || pnet.vertex[user].branch<2)
            {
                user = pnet.SourceSample();
            }
            item = pnet.TargetSample(user);
            pnet.UpdateCBOWdev(w_vertex, w_context, w_context2, user, item, dim, reg, num_events, num_words, _alpha);

            count ++;
            if (count % MONITOR == 0)
            {
                _alpha = alpha* ( 1.0 - (double)(current_sample)/total_sample_times );
                current_sample += MONITOR;
                if (_alpha < alpha_min) _alpha = alpha_min;
                alpha_last = _alpha;
                printf("\tAlpha: %.6f\tProgress: %.3f %%%c", _alpha, (double)(current_sample)/total_sample_times * 100, 13);
                fflush(stdout);
            }

        }

    }
    printf("\tAlpha: %.6f\tProgress: 100.00 %%\n", alpha_last);

}

