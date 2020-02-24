#ifndef SPARSE_ROW_MAP_H
#define SPARSE_ROW_MAP_H


class sparse_row_map : public std::map<size_t, double>
{
public:
        bool put(size_t j, double a)
        {
                if (a == 0.0)
                        return false;
                this->insert(map<size_t, double>::value_type(j,a));
                return true;
        }
        double ScalarProduct(vector<double>& x)
        {
                double product = 0.0;
                //size_t x_size = x.size();
                map<size_t, double>::iterator it;
                for(it = this->begin(); it != this->end(); it++)
                {
                        //size_t c = (*it).first;
                        //if (c < x_size)//убрал проверку, чтобы вырубались непродуманные алгоритмы
                        //{
                                product += (*it).second * x[(*it).first];
                        //}
                }
                return product;
        }
        void multip_equal (double x)
        {
                map<size_t, double>::iterator it;
                for(it = this->begin(); it != this->end(); it++)
                {
                        (*it).second *= x;
                }
        }

        void multip_equal (vector<double>& x)
        {
                //size_t x_size = x.size();
                map<size_t, double>::iterator it;
                for(it = this->begin(); it != this->end(); it++)
                {
                        //size_t c = (*it).first;
                        //if (c < x_size)//убрал проверку, чтобы вырубались непродуманные алгоритмы
                        //{
                                //this->val().val *= x[this->val().col];
                                (*it).second *= x[(*it).first];
                        //}
                }
        }
        double Sum()
        {
                double sum = 0.0;
                map<size_t, double>::iterator it;
                for(it = this->begin(); it != this->end(); it++)
                {
                        sum += (*it).second;
                }
                return sum;
        }
        double SumExcludeColomn(size_t col)
        {
                double sum = 0.0;
                map<size_t, double>::iterator it;
                for(it = this->begin(); it != this->end(); it++)
                {
                        if (col != (*it).first)
                        {
                                sum += (*it).second;
                        }
                }
                return sum;
        }
        bool replace(size_t j, double a)
        {
                std::map<size_t, double>::iterator found = this->find(j);
                if (found != this->end())
                {
                        (*found).second = a;
                }
                else
                {
                        this->put(j, a);
                }
                return true;
        }


        friend Archive& operator <<(Archive& ar, sparse_row_map& ob);
        friend Archive& operator >>(Archive& ar, sparse_row_map& ob);

};

#endif // SPARSE_ROW_MAP_H

