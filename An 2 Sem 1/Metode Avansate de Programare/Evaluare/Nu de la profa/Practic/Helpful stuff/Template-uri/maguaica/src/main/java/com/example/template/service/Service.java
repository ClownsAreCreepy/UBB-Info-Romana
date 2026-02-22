package com.example.template.service;

import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class Service {
    private final Map<Long, DTO> activeClients = new HashMap<>();
    private List<Observer<UtilizatorEntityChangeEvent>> observers=new ArrayList<>();
    public Service(Repository<Long,Persoana>repoPersoana,Repository<Long,Sofer>repoSofer,PagingComenzi<Long,Comanda>repoComanda,Repository<Long,Cerere>repoCerere,Repository<Long,Oferta>repoOferta) {
        this.repoPersoana = repoPersoana;
        this.repoSofer = repoSofer;
        this.repoComanda = repoComanda;
        this.repoCerere = repoCerere;
        this.repoOferta = repoOferta;

    }

    @Override
    public void addObserver(Observer<UtilizatorEntityChangeEvent> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<UtilizatorEntityChangeEvent> e) {

    }

    @Override
    public void notifyObservers(UtilizatorEntityChangeEvent t) {
        observers.stream().forEach(x->x.update(t));
    }
    public Page<Persoana> getPagedPersoaneForSoferID(Long userID, Pageable pageable){

        Page<Long> page = repoComanda.getPagedPersoaneForSoferID(userID,pageable);
        List<Persoana> personList = new ArrayList<>();

        for(Long ID: page.getElementsOnPage()){
            Optional<Persoana> user = repoPersoana.findOne(ID);
            user.ifPresent(personList::add);
        }
        return new Page<>(page.getTotalNumberElements(),personList);
    }

    public void removeActiveClient(Long id) {
        activeClients.remove(id);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.DELETE, null, null));
    }
    public void addActiveClient(Long id,DTO client){
        activeClients.put(id, client);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.ADD, null, null));
    }

    public int getActiveUsers(Long id) {
        DTO currentClient = activeClients.get(id);
        if (currentClient == null) {
            return 0;
        }
        return (int) activeClients.entrySet().stream()
                .filter(entry -> !entry.getKey().equals(id))
                .map(Map.Entry::getValue)
                .filter(client -> {
                    System.out.println(client);
                    return client.getLocatie().equals(currentClient.getLocatie()) &&
                            client.getData1().equals(currentClient.getData1()) &&
                            client.getData2().equals(currentClient.getData2()) &&
                            dbClient.findOne(client.getClientId()).map(Client::getHobbies).orElse(null)
                                    .equals(dbClient.findOne(currentClient.getClientId()).map(Client::getHobbies).orElse(null));
                })
                .count();
    }

    public List<SpecialOffer> getAllOferteFilt(Long id, String locatie, LocalDate data1, LocalDate data2) {
        addActiveClient(id,new DTO(id,locatie,data1,data2));  ///neaparat asta
        Iterable<SpecialOffer> oferte = dbSpecialOffer.findAllOffer();
        return StreamSupport.stream(oferte.spliterator(), false)
                .filter(offer -> offer.getStartDate().equals(data1) && offer.getEndDate().equals(data2) && findHotel(offer.getHotelId()).getLocationName().equals(locatie))
                .collect(Collectors.toList());
    }



}
