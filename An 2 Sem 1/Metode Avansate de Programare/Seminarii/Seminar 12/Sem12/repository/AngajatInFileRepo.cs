using Sem12.Model;
using Sem12.Model.Validator;

namespace Sem12.Repository;

public class AngajatInFileRepo : InFileRepository<string, Angajat>
{
    public AngajatInFileRepo(IValidator<Angajat> validator, 
        string fileName) : 
        base(validator, fileName, AngajatParser.CreateEntity, AngajatParser.SaveEntity)
    {
    }
}

public class AngajatParser
{
    public static Angajat CreateEntity(string line)
    {
        var tokens = line.Split(",");
        return new Angajat
        {
            ID = tokens[0],
            Nume = tokens[1],
            VenitPeOra = double.Parse(tokens[2]),
            Nivel = Enum.Parse<KnowledgeLevel>(tokens[3])
        };
    }

    public static string SaveEntity(Angajat entity)
    {
        return string.Join(",", entity.ID, entity.Nume, entity.VenitPeOra, entity.Nivel);
    }
}