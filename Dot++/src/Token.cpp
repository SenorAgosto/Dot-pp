#include <Dot++/Token.hpp>

namespace dot_pp {
    
    Token::Token()
        : type_(TokenType::string)
        , ready_(false)
    {
    }
    
    void Token::clear()
    {
        value_.clear();
        ready_ = false;
    }
    
    void Token::swap(Token& t)
    {
        value_.swap(t.value_);
        
        using std::swap;
        swap(type_, t.type_);
        swap(ready_, t.ready_);
    }
}
