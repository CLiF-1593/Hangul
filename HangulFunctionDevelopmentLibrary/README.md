# Hangul Function Development Library

> 한글(.hangul)에서 사용 가능한 함수를 제작할 수 있는      
> 함수 제작 C++ 라이브러리 입니다.      

### 사용법
```cpp
class Hangul {
public:
	vector<Variable> parameter_value;
	vector<vector<Variable>> parameter_list;
	Variable Function(); //TODO : Define The Function
};
```
```Hangul::Function()``` 함수를 오버라이딩하여 제작할 수 있습니다.      
main 함수는 라이브러리 내부에 포함되므로, 작성할 필요가 없습니다.      
Hangul을 위해 구현된 Variable 타입으로 반환값을 전달할 수 있습니다.      
함수의 Parameter 값은 Hangul class에 정의된 parameter_value와 parameter_list에 들어있습니다.        
