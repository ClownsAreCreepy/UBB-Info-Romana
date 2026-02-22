package scs.service;

import scs.domain.Nevoie;
import scs.domain.Oras;
import scs.domain.Persoana;
import scs.repo.Repository;

import java.util.List;

public class NevoieService extends GenericService<Nevoie> {
    private final Repository<Persoana> persoanaRepo;


    public NevoieService(Repository<Nevoie> repo, Repository<Persoana> persoanaRepo) {
        super(repo);
        this.persoanaRepo = persoanaRepo;
    }

    public List<Nevoie> getNevoiPentruOras(Oras oras, Long loggedInUserId) {
        return repo.findAll().stream()
                .filter(n -> n.getOmInNevoie() != loggedInUserId)
                .filter(n -> {
                    Persoana creator = persoanaRepo.findOne(n.getOmInNevoie()).orElse(null);
                    return creator != null && creator.getOras() == oras;
                })
                .toList();
    }

    public List<Nevoie> getFapteBune(Long userId) {
        return repo.findAll().stream()
                .filter(n -> userId.equals(n.getOmSalvator()))
                .toList();
    }

    public void preiaNevoie(Long nevoieId, Long salvatorId) {
        Nevoie nevoie = repo.findOne(nevoieId).
                orElseThrow(() -> new RuntimeException("Nevoia nu exista!"));

        if ("Erou gasit!".equals(nevoie.getStatus())) {
            throw new RuntimeException("Aceasta nevoia si-a gasit deja un erou!");
        }

        nevoie.setOmSalvator(salvatorId);
        nevoie.setStatus("Erou gasit!");

        super.update(nevoie);
    }
}
