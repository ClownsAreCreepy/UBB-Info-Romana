package scs.service;

import scs.domain.Persoana;
import scs.repo.Repository;

public class PersoanaService extends GenericService<Persoana> {

    public PersoanaService(Repository<Persoana> repo) {
        super(repo);
    }

    public Persoana findByUsername(String username) {
        return repo.findAll().stream()
                .filter(p -> p.getUsername().equals(username))
                .findFirst()
                .orElseThrow(() -> new RuntimeException("Utilizatorul nu a fost gasit!"));
    }
}
