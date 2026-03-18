namespace CalculatorApp.Commands;

public class VarCommand : ICommand
{
    public string Name => "var";

    public void Execute(Calculator.Calculator calc, string arguments)
    {
        var name = arguments.Trim();
        
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
        
        try
        {
            calc.DeclareVariable(name);
        }
        catch
        {
            Console.WriteLine("Invalid usage");
        }
    }
}