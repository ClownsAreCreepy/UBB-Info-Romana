package scs.service;

import scs.domain.Car;
import scs.repo.CarRepository;
import scs.repo.Repository;

import java.util.List;

public class CarService extends GenericService<Car>{

    public CarService(Repository<Car> repo) {
        super(repo);
    }

    // Filter for admin view
    public List<Car> getPendingCars() {
        return ((CarRepository) repo).findByStatus("NEEDS_APPROVAL");
    }

    // send for approval
    public void requestApproval(Car car, String newComment) {
        processAsync(car, () -> {
            car.setComment(newComment);
            car.setStatus("NEEDS_APPROVAL");
            repo.update(car);
            System.out.println("Car " + car.getDenumire() + " is now PENDING");
        });
    }

    // approve
    public void approveCar(Car car) {
        processAsync(car, () -> {
            car.setStatus("APPROVED");
            repo.update(car);
            System.out.println("Car " + car.getDenumire() + " APPROVED");
        });
    }

    // reject
    public void rejectCar(Car car, String rejectionReason) {
        processAsync(car, () -> {
            car.setComment(rejectionReason);
            car.setStatus("REJECTED");
            repo.update(car);
            System.out.println("Car " + car.getDenumire() + " REJECTED");
        });
    }
}
