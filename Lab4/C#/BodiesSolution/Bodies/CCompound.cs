namespace Bodies;

public class CCompound : CBody
{
    private readonly List<CBody> _children = new();

    public IReadOnlyList<CBody> GetChildren()
    {
        return _children;
    }

    public bool AddChildBody(CBody child)
    {
        if (child is null)
        {
            return false;
        }

        if (ReferenceEquals(this, child))
        {
            return false;
        }

        if (child is CCompound compoundChild && compoundChild.ContainsBody(this))
        {
            return false;
        }

        _children.Add(child);
        return true;
    }

    public bool ContainsBody(CBody body)
    {
        foreach (var child in _children)
        {
            if (ReferenceEquals(child, body))
            {
                return true;
            }

            if (child is CCompound compound && compound.ContainsBody(body))
            {
                return true;
            }
        }

        return false;
    }

    public override double GetDensity()
    {
        double volume = GetVolume();
        if (volume == 0)
        {
            return 0;
        }

        return GetMass() / volume;
    }

    public override double GetVolume()
    {
        return _children.Sum(child => child.GetVolume());
    }

    public override double GetMass()
    {
        return _children.Sum(child => child.GetMass());
    }

    public override string ToString()
    {
        return $"Compound: Density = {GetDensity():F3}, Volume = {GetVolume():F3}, Mass = {GetMass():F3}, Children = {_children.Count}";
    }
}