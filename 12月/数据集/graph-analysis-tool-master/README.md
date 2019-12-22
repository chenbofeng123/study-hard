# SNUGAL: SNU Graph Analysis Library
## 설치 방법
원하는 저장소에 `git clone https://github.com/SNUCSE-CTA/graph-analysis-tool.git`를 하여 다운로드를 받는다.
C++11 이상을 지원하는 C++ Compiler와 3.6 버전 이상의 Python, Python Matplotlib가 설치되어 있어야 한다.
## 실행 방법
사용자 환경에 맞게 Makefile을 수정한 후 `make`한다. 설정한 executable file이 나오면 그것을 실행하면 된다.
## API
`#include "snugal.h"`

`DSGraph *parse_DSGraph(std::string file_path)`

`USGraph *parse_USGraph(std::string file_path)`

`void init_stat(DSResult *result)`

`void init_stat(USResult *result)`

`void basic_stat(DSGraph *graph, DSResult *result)`

`void basic_stat(USGraph *graph, USResult *result)`

`void connect_stat(DSGraph *graph, DSResult *result)`

`void connect_stat(USGraph *graph, USResult *result)`

`void count_stat(USGraph *graph, USResult *result)`

`void init_plot(Plot *plot)`

`void make_plot(DSGraph *graph, Plot *plot)`

`void make_plot(USGraph *graph, Plot *plot)`

`void make_html(const char *name, DSResult *result, Plot *plot)`

`void make_html(const char *name, USResult *result, Plot *plot)`
