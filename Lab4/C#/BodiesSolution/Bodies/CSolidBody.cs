namespace Bodies;

public abstract class CSolidBody : CBody
{
    private readonly double _density;

    protected CSolidBody(double density)
    {
        if (density <= 0)
        {
            throw new ArgumentException("Density must be positive", nameof(density));
        }

        _density = density;
    }

    public override double GetDensity()
    {
        return _density;
    }

    public override double GetMass()
    {
        return GetDensity() * GetVolume();
    }
}