#ifndef SPARSE_ROW_SIMPLE_H
#define SPARSE_ROW_SIMPLE_H

class sparse_row_simple : public std::vector<sparse_row_element<double> >
{
public:
        bool put(size_t j, double a)
        {
                if (a == 0.0)
                        return false;
                sparse_row_element<double> tmp(j,a);
                this->push_back(tmp);
                return true;
        }
        double ScalarProduct(vector<double>& x)
        {
                double product = 0.0;
                //size_t x_size = x.size();
                vector<sparse_row_element<double> >::iterator it;
                for(it = this->begin(); it != this->end(); it++)
                {
                        //size_t c = (*it).col;
                        //if (c < x_size)//убрал проверку, чтобы вырубались непродуманные алгоритмы
                        //{
                                product += (*it).val * x[(*it).col];
                        //}
                }
                return product;
        }
        void CorrelationCoefficient(vector<double> & x, double & k, double & Cov)
        {
                size_t len = 0;
                double
                        sum1 = 0.0,
                        sum2 = 0.0;

                //for (size_t i = 0; i < len; i++)
                //{
                //	sum1 += v1[i];
                //	sum2 += v2[i];
                //}

                //double product = 0.0;
                //size_t x_size = x.size();
                vector<sparse_row_element<double> >::iterator it;
                for(it = this->begin(); it != this->end(); it++)
                {
                        //size_t c = (*it).col;
                        //if (c < x_size)//убрал проверку, чтобы вырубались непродуманные алгоритмы
                        //{
                                //product += (*it).val * x[(*it).col];
                                sum1 += (*it).val;
                                sum2 += x[(*it).col];
                                ++len;
                        //}
                }

                double
                        mean1 = sum1 / len,
                        mean2 = sum2 / len;

                double
                        sigma1 = 0.0,
                        sigma2 = 0.0;

                Cov = 0.0;

                //for (i = 0; i < len; i++)
                //{
                //	sigma1 += (v1[i] - mean1)*(v1[i] - mean1);
                //	sigma2 += (v2[i] - mean2)*(v2[i] - mean2);
                //	Cov += (v1[i] - mean1)*(v2[i] - mean2);
                //}
                for(it = this->begin(); it != this->end(); it++)
                {
                        //size_t c = (*it).col;
                        //if (c < x_size)//убрал проверку, чтобы вырубались непродуманные алгоритмы
                        //{
                                //product += (*it).val * x[(*it).col];
                                sigma1 += ((*it).val - mean1) * ((*it).val - mean1);
                                sigma2 += (x[(*it).col] - mean2) * (x[(*it).col] - mean2);
                                Cov += ((*it).val - mean1)*(x[(*it).col] - mean2);
                        //}
                }
                k = Cov/sqrt(sigma1*sigma2);
        }




        void Reconstruct_b_by_my_as_part_of_symmetric_matrix_row(vector <double> & b_rec, long r, vector<double>& x)
        {
                //size_t x_size = x.size();
                vector<sparse_row_element<double> >::iterator it;
                for(it = this->begin(); it != this->end(); it++)
                {
                        size_t c = (*it).col;
                        //if (c < x_size)//убрал проверку, чтобы вырубались непродуманные алгоритмы
                                b_rec[r] += (*it).val * x[c];
                        if (r != c)
                        {
                                //if (r < x_size)
                                        b_rec[c] += (*it).val * x[r];
                        }
                }
        }


        double ScalarProduct_fast(sparse_row_simple & r2)
        {
                double product = 0.0;

                std::vector<sparse_row_element<double> >::iterator n1 = this->begin();
                std::vector<sparse_row_element<double> >::iterator n2 = r2.begin();

                while( n1 != this->end() && n2 != r2.end() )
                {
                        size_t c1 = (*n1).col;
                        size_t c2 = (*n2).col;

                        if (c1 == c2)
                        {
                                product += (*n1).val * (*n2).val;

                                n1++;
                                n2++;
                                continue;
                        }
                        if (c1 < c2)
                        {
                                n1++;
                        }
                        else
                        {
                                n2++;
                        }
                }
                return product;
        }
        friend Archive& operator <<(Archive& ar, sparse_row_simple& ob);
        friend Archive& operator >>(Archive& ar, sparse_row_simple& ob);

        void InverseSave(Archive& ar)
        {
                long cc;
                double value;
                vector<sparse_row_element<double> >::reverse_iterator it;
                for(it = this->rbegin(); it != this->rend(); it++)
                {
                        long cc = long((*it).col);
                        double value = (*it).val;
                        ar << cc;
                        ar << value;
                }
                //признак конца записи
                cc = -1;
                value = 0.0;
                ar << cc;
                ar << value;

        }
};

#endif // SPARSE_ROW_SIMPLE_H

