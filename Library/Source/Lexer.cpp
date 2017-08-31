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
#include "Nominal/Lexer.hpp"

namespace nominal
{

Lexer::Lexer(const char* source) :
    _source(source)
{
    next();
}

bool Lexer::next()
{
    if (skip_whitespace())
    {
        _current_state.token_type = TokenType::Symbol;

        char c = read_next();
        return _current_state.end_of_input;
    }

    // Keep the token's start index and assume it is at least length 1
    _current_state.token_start_index = _current_state.index - 1;
    _current_state.token_length = 1;

    return false;
}

TokenType Lexer::token_type() const
{
    return _current_state.token_type;
}

TokenId Lexer::token_Id() const
{
    return _current_state.token_id;
}

void Lexer::push_state()
{
    _state_stack.push(_current_state);
}

bool Lexer::pop_state(bool restore)
{
    if (_state_stack.empty())
    {
        return false;
    }
    else
    {
        if (restore)
        {
            _current_state = _state_stack.top();
        }
        _state_stack.pop();
        return true;
    }
}

char Lexer::read_next()
{
    if (_current_state.end_of_input)
    {
        return '\0';
    }
    else
    {
        char c = _source[_current_state.index++];
        if (c == '\n')
        {
            ++_current_state.line;
        }
        else if (c == '\0')
        {
            _current_state.end_of_input = true;
        }
        return c;
    }
}

char Lexer::peak_next()
{
    if (_current_state.end_of_input)
    {
        return '\0';
    }
    else
    {
        return _source[_current_state.index];
    }
}

bool Lexer::skip_whitespace()
{
    _current_state.skipped_whitespace = false;
    _current_state.skipped_new_line = false;
    return true;
}

}