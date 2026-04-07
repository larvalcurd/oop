using Bodies;

internal static class BodyReader
{
    public static CBody ReadBody()
    {
        while (true)
        {
            Console.Write("Enter body type (sphere, parallelepiped, cone, cylinder, compound): ");
            string? type = Console.ReadLine()?.Trim().ToLower();

            try
            {
                switch (type)
                {
                    case "sphere":
                        return ReadSphere();

                    case "parallelepiped":
                        return ReadParallelepiped();

                    case "cone":
                        return ReadCone();

                    case "cylinder":
                        return ReadCylinder();

                    case "compound":
                        return ReadCompound();

                    default:
                        Console.WriteLine("Unknown body type. Please try again.");
                        break;
                }
            }
            catch (ArgumentException ex)
            {
                Console.WriteLine($"Input error: {ex.Message}");
            }
        }
    }

    private static CSphere ReadSphere()
    {
        Console.Write("Enter density: ");
        double density = ConsoleInput.ReadPositiveDouble();

        Console.Write("Enter radius: ");
        double radius = ConsoleInput.ReadPositiveDouble();

        return new CSphere(density, radius);
    }

    private static CParallelepiped ReadParallelepiped()
    {
        Console.Write("Enter density: ");
        double density = ConsoleInput.ReadPositiveDouble();

        Console.Write("Enter width: ");
        double width = ConsoleInput.ReadPositiveDouble();

        Console.Write("Enter height: ");
        double height = ConsoleInput.ReadPositiveDouble();

        Console.Write("Enter depth: ");
        double depth = ConsoleInput.ReadPositiveDouble();

        return new CParallelepiped(density, width, height, depth);
    }

    private static CCone ReadCone()
    {
        Console.Write("Enter density: ");
        double density = ConsoleInput.ReadPositiveDouble();

        Console.Write("Enter base radius: ");
        double baseRadius = ConsoleInput.ReadPositiveDouble();

        Console.Write("Enter height: ");
        double height = ConsoleInput.ReadPositiveDouble();

        return new CCone(density, baseRadius, height);
    }

    private static CCylinder ReadCylinder()
    {
        Console.Write("Enter density: ");
        double density = ConsoleInput.ReadPositiveDouble();

        Console.Write("Enter base radius: ");
        double baseRadius = ConsoleInput.ReadPositiveDouble();

        Console.Write("Enter height: ");
        double height = ConsoleInput.ReadPositiveDouble();

        return new CCylinder(density, baseRadius, height);
    }

    private static CCompound ReadCompound()
    {
        var compound = new CCompound();

        Console.Write("Enter number of child bodies: ");
        int childCount = ConsoleInput.ReadNonNegativeInt();

        for (int i = 0; i < childCount; i++)
        {
            Console.WriteLine($"\nEntering child body #{i + 1}:");
            CBody child = ReadBody();

            if (!compound.AddChildBody(child))
            {
                Console.WriteLine("Failed to add child body.");
                i--;
            }
        }

        return compound;
    }
}