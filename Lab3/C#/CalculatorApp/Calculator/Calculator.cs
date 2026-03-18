using Calculator.Expressions;
using Calculator.Functions;
using System.Collections.Generic;

namespace Calculator;

public class Calculator
{
    private readonly Dictionary<string, Variable> _variables = new();
    private readonly Dictionary<string, Function> _functions = new();

    public bool VariableExists(string name) => _variables.ContainsKey(name);
    public bool FunctionExists(string name) => _functions.ContainsKey(name);
    public bool IdentifierExists(string name) => VariableExists(name) || FunctionExists(name);
    public void DeclareVariable(string name)
    {
        if (_variables.ContainsKey(name))
        {
            throw new InvalidOperationException($"Variable '{name}' already declared.");
        }

        var variable = new Variable(name);
        _variables[name] = variable;
    }

    public Variable GetVariable(string name)
    {
        if (!_variables.TryGetValue(name, out var variable))
        {
            throw new KeyNotFoundException($"Variable '{name}' not found.");
        }

        return variable;
    }

    public double GetValue(string name)
    {
        if (VariableExists(name))
        {
            return GetVariable(name).Value;
        }
        if (FunctionExists(name))
        {
            return _functions[name].Evaluate(this);
        }
        throw new KeyNotFoundException($"Identifier '{name}' not found.");
    }

    public void SetVariable(string name, double value)
    {
        if (!VariableExists(name))
        {
            DeclareVariable(name);
        }
        GetVariable(name).Value = value;
    }

    public void SetVariable(string name, string otherName)
    {
        double value = GetValue(otherName);
        SetVariable(name, value);
    }

    public void DeclareFunction(string name, string identifierName)
    {
        if (IdentifierExists(name))
        {
            throw new InvalidOperationException($"Identifier '{name}' already declared.");
        }
        var expr = new IdentifierExpression(identifierName);
        var func = new Function(name, expr);
        _functions[name] = func;
    }

    public void DeclareFunction(string name, string left, string operation, string right)
    {
        if (IdentifierExists(name))
        {
            throw new InvalidOperationException($"Identifier '{name}' already declared.");
        }
        var op = ParseOperation(operation);
        var expr = new BinaryExpression(new IdentifierExpression(left), new IdentifierExpression(right), op);
        var func = new Function(name, expr);
        _functions[name] = func;
    }

    private Operation ParseOperation(string op)
    {
        return op switch
        {
            "+" => Operation.Add,
            "-" => Operation.Subtract,
            "*" => Operation.Multiply,
            "/" => Operation.Divide,
            _ => throw new ArgumentException($"Unknown operation: {op}")
        };
    }

    public IEnumerable<Variable> GetAllVariables()
    {
        return _variables.Values.OrderBy(v => v.Name);
    }

    public IEnumerable<Functions.Function> GetAllFunctions()
    {
        return _functions.Values.OrderBy(f => f.Name);
    }
}
