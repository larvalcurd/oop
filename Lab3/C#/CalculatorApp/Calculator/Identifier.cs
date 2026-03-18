using System.Text.RegularExpressions;

namespace Calculator;

public static class Identifier
{
    private static readonly Regex ValidPattern = new(@"^[a-zA-Z_][a-zA-Z0-9_]*$");
    
    public static bool IsValid(string name)
    {
        return !string.IsNullOrWhiteSpace(name) && ValidPattern.IsMatch(name);
    }
    
    public static void Validate(string name)
    {
        if (!IsValid(name))
        {
            throw new ArgumentException($"Invalid identifier: '{name}'", nameof(name));
        }
    }
}