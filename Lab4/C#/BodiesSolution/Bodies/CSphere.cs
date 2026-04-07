namespace Bodies;

public class CSphere : CSolidBody
{
    private readonly double _radius;

    public CSphere(double density, double radius) : base(density)
    {
        if (radius <= 0)
        {
            throw new ArgumentException("Radius must be positive", nameof(radius));
        }

        _radius = radius;
    }

    public double GetRadius()
    {
        return _radius;
    }

    public override double GetVolume()
    {
        return (4.0 / 3.0) * Math.PI * Math.Pow(_radius, 3);
    }

    public override string ToString()
    {
        return $"Sphere: Radius = {_radius:F3}, {base.ToString()}";
    }
}
