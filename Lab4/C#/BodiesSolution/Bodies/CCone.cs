namespace Bodies;

public class CCone : CSolidBody
{
    private readonly double _baseRadius;
    private readonly double _height;

    public CCone(double density, double baseRadius, double height) : base(density)
    {
        if (baseRadius <= 0)
        {
            throw new ArgumentException("Base radius must be positive", nameof(baseRadius));
        }

        if (height <= 0)
        {
            throw new ArgumentException("Height must be positive", nameof(height));
        }

        _baseRadius = baseRadius;
        _height = height;
    }

    public double GetBaseRadius()
    {
        return _baseRadius;
    }

    public double GetHeight()
    {
        return _height;
    }

    public override double GetVolume()
    {
        return Math.PI * _baseRadius * _baseRadius * _height / 3.0;
    }

    public override string ToString()
    {
        return $"Cone: BaseRadius = {_baseRadius:F3}, Height = {_height:F3}, {base.ToString()}";
    }
}