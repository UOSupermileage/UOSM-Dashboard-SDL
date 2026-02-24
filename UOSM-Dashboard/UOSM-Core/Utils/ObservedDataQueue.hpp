#ifdef UOSM_OBSERVABLES

#ifndef UOSM_CORE_OBSERVEDDATAQUEUE_HPP
#define UOSM_CORE_OBSERVEDDATAQUEUE_HPP

#include "DataQueue.hpp"
#include "ObservedObject.hpp"

template<typename T>
class ObservedDataQueue : public ObservedObject<DataQueue<T>> {
private:
    DataQueue<T> queue; // Composition

public:
    explicit ObservedDataQueue(uint8_t size) : queue(size), ObservedObject<DataQueue<T>>(&queue, false) {}

    void add(T value) {
        // Gestion de la mémoire pour les pointeurs
        if constexpr (std::is_pointer<T>::value) {
            // On vérifie si la queue est pleine avant d'ajouter
            if (queue.getNumberOfElements() == queue.getSize()) {
                // On doit supprimer l'élément qui va être écrasé (le plus vieux)
                // Note : il faut que DataQueue expose un moyen d'accéder au RawValues ou au Tail
                T oldest = queue.getRawValues()[queue.getTailIndex()];
                delete oldest;
            }
        }

        // Utilisation de l'objet membre 'queue' et non de l'héritage
        queue.add(value);

        // Notification des observers (l'UI)
        this->notify();
    }

    void update(T value) {
        queue.update(value);
        this->notify(); // On notifie aussi sur un update
    }

    // --- Délégation des méthodes de DataQueue ---
    [[nodiscard]] uint8_t getSize() const { return queue.getSize(); }
    [[nodiscard]] uint8_t getNumberOfElements() const { return queue.getNumberOfElements(); }
    [[nodiscard]] T* getValues() const { return queue.getValues(); }
    [[nodiscard]] T& getLatestValue() const { return queue.getLatestValue(); }

    /**
     * Helper pour l'UI : permet d'écouter uniquement la dernière valeur
     */
    ObserverToken addListenerForLatest(std::function<void(const T&)> callback) {
        return this->addListener([this, callback](const DataQueue<T>& q) {
            if (queue.getNumberOfElements() > 0) {
                callback(queue.getLatestValue());
            }
        });
    }
};

#endif //UOSM_CORE_OBSERVEDDATAQUEUE_HPP
#endif