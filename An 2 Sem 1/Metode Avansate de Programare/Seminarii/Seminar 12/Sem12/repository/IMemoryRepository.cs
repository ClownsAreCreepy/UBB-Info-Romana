using Sem12.Model;
using Sem12.Model.Validator;

namespace Sem12.Repository;

public class InMemoryRepository<TId, T> : IRepository<TId, T> where T : Entity<TId>
{
    protected IValidator<T> Validator;
    protected IDictionary<TId, T> Entities;
    
    public InMemoryRepository(IValidator<T> validator)
    {
        Validator = validator;
        Entities = new OrderedDictionary<TId, T>();
    }
    
    
    public T? FindOne(TId id)
    {
        Entities.TryGetValue(id, out var entity);
        return entity;
    }

    public IEnumerable<T> FindAll()
    {
        return Entities.Values.ToList();
    }

    public virtual T? Save(T entity)
    {
        if (Entities.TryGetValue(entity.ID, out var existingEntity))
            return existingEntity;
        
        Validator.Validate(entity);
        return Entities[entity.ID] = entity;
    }

    public virtual T? Delete(TId id)
    {
        if (!Entities.TryGetValue(id, out var existingEntity))
            return null;
        
        Entities.Remove(id);
        return existingEntity;
    }

    public virtual T? Update(T entity)
    {
        if (!Entities.ContainsKey(entity.ID))
            return null;
        
        Validator.Validate(entity);
        return Entities[entity.ID] = entity;
    }
}