#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<miko/rall_cout.hpp>
#include<fstream>
#include<chrono>
#include<thread>

template<class Range,class Function>
void replace(Range& s,const char* src,const char* dst,Function f)
{
	const size_t src_len=strlen(src);
	const size_t dst_len=strlen(dst);

        for(std::string& str:s){
                for(std::string::size_type i=0;
                                (i=str.find(src,i,src_len))!=std::string::npos;
                                i+=dst_len){
                        str.replace(i,src_len,dst,dst_len);
                        f(s);
                }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
}

template<class Range>
typename Range::size_type max_elements(const Range& r)
{
        std::vector<int> v;
        for(auto str:r)
                v.push_back(str.size());
        return *std::max_element(v.begin(),v.end());
}

int main(const int argc,const char* argv[])
{
	if(argc<2)return -1;
	std::ifstream ifs(argv[1]);
	if(!ifs.is_open())return -1;

	std::vector<std::string> ar;
        std::string line;
	while(std::getline(ifs,line))
                ar.push_back(line);

        const size_t max_element=max_elements(ar);
        for(std::string& str:ar){
                const size_t loop=max_element-str.length();
                for(size_t j=0; j<loop; ++j)
                        str.push_back(' ');
                str.push_back('\n');
        }

        replace(ar," ",argc==3?argv[2]:"0",[](const std::vector<std::string>&){});
        replace(ar,argc==3?argv[2]:"0"," ",[](const std::vector<std::string>& s){
                        system("clear");
                        miko::rall_cout<<s;
                        });
}
