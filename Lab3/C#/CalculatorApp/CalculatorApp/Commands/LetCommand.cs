using System.Text.RegularExpressions;

namespace CalculatorApp.Commands;

public class LetCommand : ICommand
{
    public string Name => "let";

    public void Execute(Calculator.Calculator calc, string arguments)
    {   
        var parts = arguments.Split('=', 2);
        
        if (parts.Length != 2)
        {
            Console.WriteLine("Invalid usage");
            return;
        }
        
        string name = parts[0].Trim();
        string valueStr = parts[1].Trim();
        
        if (!Calculator.Identifier.IsValid(name))
        {
            Console.WriteLine("Invalid usage");
            return;
        }
        
        if (calc.FunctionExists(name))
        {
            Console.WriteLine("Invalid usage");
            return;
        }
        
        if (double.TryParse(valueStr, out double numericValue))
        {
            calc.SetVariable(name, numericValue);
            return;
        }
        
        if (Calculator.Identifier.IsValid(valueStr))
        {
            if (!calc.IdentifierExists(valueStr))
            {
                Console.WriteLine("Name does not exist");
                return;
            }
            
            calc.SetVariable(name, valueStr);
            return;
        }
        
        Console.WriteLine("Invalid usage");
    }
}