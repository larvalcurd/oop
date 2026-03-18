namespace CalculatorApp.Commands;

public class PrintCommand : ICommand
{
    public string Name => "print";

    public void Execute(Calculator.Calculator calc, string arguments)
    {
        var name = arguments.Trim();
        
        if (!calc.IdentifierExists(name))
        {
            Console.WriteLine("Name does not exist");
            return;
        }
        
        double value = calc.GetValue(name);
        
        if (double.IsNaN(value))
        {
            Console.WriteLine("nan");
        }
        else
        {
            Console.WriteLine(value.ToString("F2"));
        }
    }
}