///////////////////////////////////////////////////////////////////////////////
// This source file is part of Nominal.
//
// Copyright (c) 2017 Colin Hill
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Export.hpp"
#include <stack>

namespace nominal
{

enum class TokenType
{
    Symbol,
    Operator,
    Identifier,
    String,
    Number
};

typedef unsigned TokenId;

class NOM_EXPORT Lexer
{
public:
    Lexer(const char* source);

    bool next();

    TokenType token_type() const;
    TokenId token_Id() const;

    void push_state();
    bool pop_state(bool restore);

private:
    char read_next();
    char peak_next();
    bool skip_whitespace();

    struct State
    {
        unsigned index{ 0 };
        unsigned line{ 0 };
        unsigned token_start_index{ 0 };
        unsigned token_length{ 0 };
        TokenType token_type{ TokenType::Symbol };
        TokenId token_id{ 0 };
        bool skipped_whitespace{ false };
        bool skipped_new_line{ false };
        bool end_of_input{ false };
    };

    const char* _source;
    State _current_state;
    std::stack<State> _state_stack;
};

}
