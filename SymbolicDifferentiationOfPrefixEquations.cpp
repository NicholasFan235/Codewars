#include <bits/stdc++.h>

class term{
public:
    std::string value;
    term *t1 = nullptr, *t2 = nullptr;
public:
    term(){
        t1 = nullptr;
        t2 = nullptr;
    };
    term(const term& t) = default;
    term(std::string v){
        value = v;
        t1 = nullptr;
        t2 = nullptr;
    }
    ~term(){
        //std::cout << "Deleting " << value << std::endl;
        delete t1;
        delete t2;
    };

    term* diff();
    std::string toString();
    void trim();
    void deepCopy(const term &src);
};

term *operation;
std::vector<std::string> singleArgOperations = { "sin", "cos", "ln", "exp", "tan" };

bool isNum(const std::string &s){
    return std::isdigit(s.front()) || std::isdigit(s.back());
}

void term::deepCopy(const term &src){
    value = src.value;
    delete t1; delete t2;
    if (src.t1 != nullptr){
        t1 = new term();
        t1->deepCopy(*src.t1);
    }
    if (src.t2 != nullptr) {
        t2 = new term();
        t2->deepCopy(*src.t2);
    }
}

term* MakeCopy(const term& src){
    term* t = new term();
    t->deepCopy(src);
    return t;
}

std::string trimString(std::string s){
    if (s.find('.') != s.npos){
        while (s.back() == '0'){
            s.pop_back();
        }
        if (s.back() == '.'){
            s.pop_back();
        }
    }
    return s;
}

void term::trim(){
    //std::cout << toString() << std::endl;
    if (t1 != nullptr) t1->trim();
    if (t2 != nullptr) t2->trim();

    if (value.compare("*")==0){
        if (t1->value.compare("0") == 0 || t2->value.compare("0") == 0){
            //std::cout << t1 << ", " << t2 << std::endl;
            delete t1;
            delete t2;
            t1 = nullptr;
            t2 = nullptr;
            value = "0";
            return;
        }
        if (isNum(t1->value) && isNum(t2->value)){
            double a = std::stod(t1->value);
            double b = std::stod(t2->value);
            delete t1;
            delete t2;
            t1 = nullptr;
            t2 = nullptr;
            value = trimString(std::to_string(a*b));
            return;
            //std::cout << a << " * " << b << " = " << value << std::endl;
        }
        if (t2->value.compare("1") == 0){
            value = t1->value;
            delete t2;
            t2 = nullptr;
            t2 = t1->t2;
            t1 = t1->t1;
            return;
        }
        if (t1->value.compare("1") == 0){
            value = t2->value;
            delete t1;
            t1 = nullptr;
            t1 = t2->t1;
            t2 = t2->t2;
            return;
        }
    }
    else if(value.compare("/") == 0){
        if (t2->value.compare("1") == 0){
            value = t1->value;
            delete t2;
            t2 = nullptr;
            t2 = t1->t2;
            t1 = t1->t1;
            return;
        }
        if (t1->value.compare("0") == 0){
            delete t1;
            delete t2;
            t1 = nullptr;
            t2 = nullptr;
            value = "0";
            return;
        }
        if (isNum(t1->value) && isNum(t2->value)){
            double a = std::stod(t1->value);
            double b = std::stod(t2->value);
            delete t1;
            delete t2;
            t1 = nullptr;
            t2 = nullptr;
            value = trimString(std::to_string(a/b));
            return;
            //std::cout << a << " / " << b << " = " << value << std::endl;
        }
    }
    else if(value.compare("+") == 0){
        if (t2->value.compare("0") == 0){
            value = t1->value;
            delete t2;
            t2 = nullptr;
            t2 = t1->t2;
            t1 = t1->t1;
            return;
        }
        if (t1->value.compare("0") == 0){
            value = t2->value;
            delete t1;
            t1 = nullptr;
            t1 = t2->t1;
            t2 = t2->t2;
            return;
        }
        if (isNum(t1->value) && isNum(t2->value)){
            double a = std::stod(t1->value);
            double b = std::stod(t2->value);
            delete t1;
            delete t2;
            t1 = nullptr;
            t2 = nullptr;
            value = trimString(std::to_string(a+b));
            return;
            //std::cout << a << " + " << b << " = " << value << std::endl;
        }
    }
    else if(value.compare("-") == 0){
        if (t2->value.compare("0") == 0){
            value = t1->value;
            delete t2;
            t2 = nullptr;
            t2 = t1->t2;
            t1 = t1->t1;
            return;
        }
        if (isNum(t1->value) && isNum(t2->value)){
            double a = std::stod(t1->value);
            double b = std::stod(t2->value);
            delete t1;
            delete t2;
            t1 = nullptr;
            t2 = nullptr;
            value = trimString(std::to_string(a-b));
            return;
            //std::cout << a << " - " << b << " = " << value << std::endl;
        }
    }
    else if(value.compare("^") == 0){
        if (isNum(t1->value) && isNum(t2->value)){
            double a = std::stod(t1->value);
            double b = std::stod(t2->value);
            delete t1;
            delete t2;
            t1 = nullptr;
            t2 = nullptr;
            value = trimString(std::to_string(pow(a,b)));
            return;
            //std::cout << a << " ^ " << b << " = " << value << std::endl;
        }
        if (t2->value.compare("0") == 0){
            //std::cout << t1 << ", " << t2 << std::endl;
            delete t1;
            delete t2;
            t1 = nullptr;
            t2 = nullptr;
            value = "1";
            return;
        }
        if (t1->value.compare("0") == 0){
            //std::cout << t1 << ", " << t2 << std::endl;
            delete t1;
            delete t2;
            t1 = nullptr;
            t2 = nullptr;
            value = "0";
            return;
        }
        if (t2->value.compare("1") == 0){
            value = t1->value;
            delete t2;
            t2 = nullptr;
            t2 = t1->t2;
            t1 = t1->t1;
            return;
        }
    }
    return;
}

std::string term::toString(){
    std::string result;
    if (t1 != nullptr){
        result += "(" + value + " ";
        result += t1->toString();
        if (t2 != nullptr){
            result += " " + t2->toString();
        }
        result += ")";
    }
    else{
        result += value;
    }
    return result;
}

term* term::diff(){
    if (value.compare("*") == 0){
        term* result = new term("+");
        result->t1 = new term("*");
        result->t1->t1 = MakeCopy(*t1);
        result->t1->t2 = MakeCopy(*t2->diff());

        result->t2 = new term("*");
        result->t2->t1 = MakeCopy(*t1->diff());
        result->t2->t2 = MakeCopy(*t2);
        return result;
    }
    else if (value.compare("/") == 0){
        if (isdigit(t2->value[0])){
            double b = std::stod(t2->value);
            b = 1/b;
            term* result = new term("*");
            result->t1 = t1->diff();
            result->t2 = new term(trimString(std::to_string(b)));
            return result;
        }
        term* result = new term("/");
        result->t1 = new term("-");
        result->t1->t1 = new term("*");
        result->t1->t2 = new term("*");
        result->t1->t1->t1 = MakeCopy(*t1->diff());
        result->t1->t1->t2 = MakeCopy(*t2);
        result->t1->t2->t1 = MakeCopy(*t1);
        result->t1->t2->t2 = MakeCopy(*t2->diff());

        result->t2 = new term("^");
        result->t2->t1 = MakeCopy(*t2);
        result->t2->t2 = new term("2");
        return result;
    }
    else if (value.compare("+") == 0){
        term* result = new term("+");
        result->t1 = MakeCopy(*t1->diff());
        result->t2 = MakeCopy(*t2->diff());
        return result;
    }
    else if (value.compare("-") == 0){
        term* result = new term("-");
        result->t1 = MakeCopy(*t1->diff());
        result->t2 = MakeCopy(*t2->diff());
        return result;
    }
    else if(value.compare("^") == 0){
        double b = std::stod(t2->value);
        term* result = new term("*");
        result->t1 = new term(trimString(std::to_string(b)));

        result->t2 = new term("*");
        result->t2->t1 = new term("^");
        result->t2->t1->t1 = MakeCopy(*t1);
        result->t2->t1->t2 = new term(trimString(std::to_string(b-1)));
        result->t2->t2 = MakeCopy(*t1->diff());
        return result;
    }
    else if(value.compare("sin") == 0){
        term* result = new term("*");
        result->t1 = MakeCopy(*t1->diff());
        result->t2 = new term("cos");
        result->t2->t1 = MakeCopy(*t1);
        return result;
    }
    else if(value.compare("cos") == 0){
        term* result = new term("*");
        result->t1 = new term("*");
        result->t1->t1 = new term("-1");
        result->t1->t2 = MakeCopy(*t1->diff());
        result->t2 = new term("sin");
        result->t2->t1 = MakeCopy(*t1);
        return result;
    }
    else if(value.compare("tan") == 0){
        term* result = new term("*");
        result->t1 = MakeCopy(*t1->diff());
        result->t2 = new term("^");
        result->t2->t1 = new term("cos");
        result->t2->t1->t1 = MakeCopy(*t1);
        result->t2->t2 = new term("-2");
        return result;
    }
    else if(value.compare("exp") == 0){
        term* result = new term("*");
        result->t1 = MakeCopy(*t1->diff());
        result->t2 = new term("exp");
        result->t2->t1 = MakeCopy(*t1);
        return result;
    }
    else if (value.compare("ln") == 0){
        term* result = new term("/");
        result->t1 = MakeCopy(*t1->diff());
        result->t2 = MakeCopy(*t1);
        return result;
    }
    else if(value.compare("x") == 0){
        return new term("1");
    }
    else{
        //std::cout << value << std::endl;
        return new term("0");
    }
}

std::string getTerm(std::stringstream &ss){
    std::string result;
    std::string t;
    int brackets = 0;
    while (1){
        ss >> t;
        result += t + " ";
        for (int i = 0; i < t.length(); i++){
            if (t[i] != '(') break;
            brackets++;
        }
        for (int i = t.length()-1; i >= 0; i--){
            if (t.back() != ')') break;
            t.pop_back();
            brackets--;
        }
        while (brackets <= 0){
            if (brackets == 0){
                result.pop_back();
                return result;
            }
            brackets++;
            result.pop_back();
        }
    }
    return result;
}

void makeOperation(term* currentTerm, const std::string s){
    //std::cout << "\"" << s << "\"" << std::endl;
    if (s[0] == '('){
        std::stringstream ss;
        ss.str(s);

        std::string t;
        ss >> t;
        currentTerm -> value = t.substr(1);
        currentTerm -> t1 = new term();
        makeOperation(currentTerm->t1, getTerm(ss));
        
        if (std::find(singleArgOperations.begin(), singleArgOperations.end(), currentTerm->value) == singleArgOperations.end()){
            currentTerm -> t2 = new term();
            makeOperation(currentTerm->t2, getTerm(ss));
        }
    }
    else{
        currentTerm -> value = s;
    }
}

std::string diff(const std::string &s){
    std::cout << s << "\t->\t";
    operation = new term();
    makeOperation(operation, s);
    term *dO = operation->diff();

    //std::cout << operation->toString();
    //std::cout << "\t" << dO->toString() << std::endl;
    dO->trim();

    std::stringstream oss;
    oss << dO->toString();
    std::string result = oss.str();

    std::cout << result << std::endl;

    return result;
}

std::vector<std::string> queries = {
    "5",
    "x",
    "(+ x x)",
    "(- x x)",
    "(* x 2)",
    "(/ x 2)",
    "(^ x 2)",
    "(cos x)",
    "(sin x)",
    "(exp x)",
    "(ln x)",
    "(+ x (+ x x))",
    "(- (+ x x) x)",
    "(* 2 (+ x 2))",
    "(/ 2 (+ 1 x))",
    "(cos (+ x 1))",
    "(sin (+ x 1))",
    "(sin (* 2 x))",
    "(exp (* 2 x))",
    "(tan (* 2 x)",
    "(cos (* 96 x))",
};

int main(){
    for (const auto q : queries){
        diff(q);
    }
    return 0;
}