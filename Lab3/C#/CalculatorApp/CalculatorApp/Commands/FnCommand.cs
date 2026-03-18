using System.Text.RegularExpressions;

namespace CalculatorApp.Commands;

public class FnCommand : ICommand
{
    public string Name => "fn";
    
    private static readonly Regex BinaryExpressionPattern = new(
        @"^([a-zA-Z_][a-zA-Z0-9_]*)\s*([+\-*/])\s*([a-zA-Z_][a-zA-Z0-9_]*)$"
    );

    public void Execute(Calculator.Calculator calc, string arguments)
    {
        var parts = arguments.Split('=', 2);
        
        if (parts.Length != 2)
        {
            Console.WriteLine("Invalid usage");
            return;
        }
        
        string name = parts[0].Trim();
        string expression = parts[1].Trim();
        
        if (!Calculator.Identifier.IsValid(name))
        {
            Console.WriteLine("Invalid usage");
            return;
        }
        
        if (calc.IdentifierExists(name))
        {
            Console.WriteLine("Name already exists");
            return;
        }
        
        var match = BinaryExpressionPattern.Match(expression);
        if (match.Success)
        {
            string left = match.Groups[1].Value;
            string op = match.Groups[2].Value;
            string right = match.Groups[3].Value;
            
            try
            {
                calc.DeclareFunction(name, left, op, right);
            }
            catch
            {
                Console.WriteLine("Invalid usage");
            }
            return;
        }
        
        if (Calculator.Identifier.IsValid(expression))
        {
            try
            {
                calc.DeclareFunction(name, expression);
            }
            catch
            {
                Console.WriteLine("Invalid usage");
            }
            return;
        }
        
        Console.WriteLine("Invalid usage");
    }
}