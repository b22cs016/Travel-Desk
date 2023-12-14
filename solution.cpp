#include <iostream>
#include <vector>
#include <map>
#include <bits/stdc++.h>
using namespace std;
class Vehicle;

class Trip
{
public:
    Trip(Vehicle *vehicle, std::string pick_up_location, std::string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle *getVehicle() const
    {
        return vehicle;
    }

    std::string getPickUpLocation() const
    {
        return pick_up_location;
    }

    std::string getDropLocation() const
    {
        return drop_location;
    }

    int getDepartureTime() const
    {
        return departure_time;
    }

    int getBookedSeats() const
    {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle *v)
    {
        vehicle = v;
    }

    void setPickUpLocation(std::string location)
    {
        pick_up_location = location;
    }

    void setDropLocation(std::string location)
    {
        drop_location = location;
    }

    void setDepartureTime(int time)
    {
        departure_time = time;
    }

    void setBookedSeats(int seats)
    {
        booked_seats = seats;
    }

private:
    Vehicle *vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
};

class BinaryTreeNode
{
public:
    BinaryTreeNode(int departuretime = 0, Trip *tripenodeptr = nullptr, BinaryTreeNode *parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode *getLeftPtr() const
    {
        return leftptr;
    }

    BinaryTreeNode *getRightPtr() const
    {
        return rightptr;
    }

    BinaryTreeNode *getParentPtr() const
    {
        return parentptr;
    }

    int getDepartureTime() const
    {
        return departuretime;
    }

    Trip *getTripNodePtr() const
    {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode *left)
    {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode *right)
    {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode *parent)
    {
        parentptr = parent;
    }

    void setDepartureTime(int time)
    {
        departuretime = time;
    }

    void setTripNodePtr(Trip *trip)
    {
        tripnodeptr = trip;
    }

private:
    BinaryTreeNode *leftptr;
    BinaryTreeNode *rightptr;
    BinaryTreeNode *parentptr;
    int departuretime;
    Trip *tripnodeptr;
};

class TransportService
{
public:
    std::vector<Trip *> trips;

    TransportService(std::string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    std::string getName() const
    {
        return name;
    }

    BinaryTreeNode *getBSTHead() const
    {
        return BSThead;
    }

    // Setter functions
    void setName(std::string service_name)
    {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode *node)
    {
        BSThead = node;
    }

    void addTrip(int key, Trip *trip)
    {
        BinaryTreeNode *new_node = new BinaryTreeNode();
        new_node->setDepartureTime(key);
        new_node->setTripNodePtr(trip);
        // new_node->setDepartureTime(key);
        // new_node->setTripNodePtr(trip);

        if (getBSTHead() == nullptr)
        {
            setBSTHead(new_node);
            return;
        }
        BinaryTreeNode *iter = getBSTHead();
        BinaryTreeNode *parentptr = iter;
        while (iter != nullptr)
        {
            if (iter->getDepartureTime() > key)
            {
                parentptr = iter;
                iter = iter->getLeftPtr();
            }
            else
            {
                parentptr = iter;
                iter = iter->getRightPtr();
            }
        }
        if (parentptr->getDepartureTime() > new_node->getDepartureTime())
        {
            parentptr->setLeftPtr(new_node);
        }
        else
        {
            parentptr->setRightPtr(new_node);
        }
    };
    void trips_within_specified_range(BinaryTreeNode *node, int lower, int upper)
    {
        if (node == nullptr)
        {
            return;
        }
        trips_within_specified_range(node->getLeftPtr(), lower, upper);
        if (node->getDepartureTime() >= lower && node->getDepartureTime() <= upper)
        {
            trips.push_back(node->getTripNodePtr());
        }
        trips_within_specified_range(node->getRightPtr(), lower, upper);
    }

private:
    std::string name;
    BinaryTreeNode *BSThead;
};

class Vehicle
{
public:
    std::vector<Trip *> trips;
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    std::string getVehicleNumber() const
    {
        return vehicle_number;
    }

    int getSeatingCapacity() const
    {
        return seating_capacity;
    }

    // Setter functions
    void setVehicleNumber(std::string number)
    {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity)
    {
        seating_capacity = capacity;
    }

    void addTrip(Trip *trip)
    {
        trips.push_back(trip);
    }
    std::vector<Trip *> getTrips() const
    {
        return trips;
    };

private:
    std::string vehicle_number;
    int seating_capacity;
};

class Location
{
public:
    std::vector<TransportService *> serviceptrs;
    Location(std::string name) : name(name) {}

    // Getter functions
    std::string getName() const
    {
        return name;
    }
    TransportService *setServicePtr(std::string droplocation)
    {
        TransportService *new_service_ptr = new TransportService(getName().append(droplocation));
        serviceptrs.push_back(new_service_ptr);
        return new_service_ptr;
    }

    TransportService *getServicePtr(std::string droplocation)
    {

        for (int i = 0; i < serviceptrs.size(); i++)
        {
            if (serviceptrs[i]->getName().find(droplocation) != string::npos)
            {
                return serviceptrs[i];
            }
        }
        TransportService *new_transport_service = new TransportService(getName().append(droplocation));
        serviceptrs.push_back(new_transport_service);
        return new_transport_service;
    }

    // Setter functions
    void setName(std::string location_name)
    {
        name = location_name;
    }

    void addTrip(Trip *trip)
    {
        trips.push_back(trip);
    }

private:
    std::string name;

    std::vector<Trip *> trips;
};

class BinaryTree
{
protected:
    BinaryTreeNode *root;

public:
    BinaryTree() : root(nullptr) {}

    int getHeight() const
    {
        int height = heightofBinaryTree(root);
        return height; // Placeholder
    }
    int heightofBinaryTree(BinaryTreeNode *node) const
    {
        if (node == NULL)
            return 0;
        else
        {
            /* compute the depth of each subtree */
            int heightofLeftSubtree = heightofBinaryTree(node->getLeftPtr());
            int heightofRightSubtree = heightofBinaryTree(node->getRightPtr());

            /* use the larger one */
            if (heightofLeftSubtree > heightofRightSubtree)
                return (heightofLeftSubtree + 1);
            else
                return (heightofRightSubtree + 1);
        }
    }

    int getNumberOfNodes() const
    {
        int totalnodes = totalNumberofNodes(root);
        return totalnodes;
    }
    int totalNumberofNodes(BinaryTreeNode *node) const
    {
        if (node == nullptr)
        {
            return 0;
        }
        else
        {
            return (1 + totalNumberofNodes(node->getLeftPtr()) + totalNumberofNodes(node->getRightPtr()));
        }
    }
};

class BinarySearchTree : public BinaryTree
{
public:
    BinarySearchTree() {}

    BinaryTreeNode *getElementWithMinimumKey() const
    {
        BinaryTreeNode *iter = root;
        while (iter->getLeftPtr() != nullptr)
        {
            iter = iter->getLeftPtr();
        }

        // Implement this function to return the element with the minimum key
        return iter; // Placeholder
    }

    BinaryTreeNode *getElementWithMaximumKey() const
    {
        // Implement this function to return the element with the maximum key
        BinaryTreeNode *iter = root;
        while (iter->getRightPtr() != nullptr)
        {
            iter = iter->getRightPtr();
        }
        return iter;
    }

    BinaryTreeNode *searchNodeWithKey(int key) const
    {
        // Implement this function to search for a node with the given key or the next larger key
        BinaryTreeNode *iter = root;
        while (iter != nullptr)
        {
            if (iter->getDepartureTime() > key)
            {
                iter = iter->getLeftPtr();
            }
            else if (iter->getDepartureTime() < key)
            {
                iter = iter->getRightPtr();
            }
            else
            {
                break;
            }
        }
        return iter;
    }

    BinaryTreeNode *getSuccessorNode(BinaryTreeNode *node) const
    {
        // Implement this function to return the successor node of the given node
        if (node->getRightPtr() != nullptr)
        {
            BinaryTreeNode *iter = node->getRightPtr();
            while (iter->getLeftPtr() != nullptr)
            {
                iter = iter->getLeftPtr();
            }
            return iter;
        }

        BinaryTreeNode *succ = nullptr;
        BinaryTreeNode *iter = root;
        while (iter->getDepartureTime() != node->getDepartureTime())
        {
            if (node->getDepartureTime() < iter->getDepartureTime())
            {
                succ = node;
                iter = iter->getLeftPtr();
            }
            else
            {
                iter = iter->getRightPtr();
            }
        }
        return succ;
    }

    BinaryTreeNode *getSuccessorNodeByKey(int key) const
    {
        BinaryTreeNode *find_succ_of_node = searchNodeWithKey(key);
        return getSuccessorNode(find_succ_of_node);
    }

    BinaryTreeNode *getPredecessorNode(BinaryTreeNode *node) const
    {
        BinaryTreeNode *iter = root;
        if (iter == nullptr)
        {
            return nullptr;
        }
        BinaryTreeNode *pred = nullptr;
        while (iter != nullptr)
        {
            if (node->getDepartureTime() < iter->getDepartureTime())
            {
                iter = iter->getLeftPtr();
            }
            else if (node->getDepartureTime() > iter->getDepartureTime())
            {
                pred = iter;
                iter = iter->getRightPtr();
            }
            else
            {
                if (iter->getLeftPtr() != nullptr)
                {
                    iter = iter->getLeftPtr();
                    while (iter->getRightPtr() != nullptr)
                    {
                        iter = iter->getRightPtr();
                    }
                    pred = iter;
                    return pred;
                }
                break;
            }
        }
        return pred;
    }

    BinaryTreeNode *getPredecessorNodeByKey(int key) const
    {
        // Implement this function to return the predecessor node by key
        // Placeholder
        BinaryTreeNode *node_to_find_pred = searchNodeWithKey(key);
        return getPredecessorNode(node_to_find_pred);
    }
    std::vector<Trip *> search_within_range(int lower, int upper)
    {
        std::vector<Trip *> array_of_trips;
        BinaryTreeNode *iter;
        iter = searchNodeWithKey(lower);
        while (iter == nullptr)
        {
            lower++;
        }

        while (iter->getDepartureTime() <= upper)
        {
            array_of_trips.push_back(iter->getTripNodePtr());
            iter = getSuccessorNode(iter);
        }
        return array_of_trips;
    };
    BinaryTreeNode* deleteNode(BinaryTreeNode* root, int k)
{
    // Base case
    if (root == NULL)
        return root;
 
    // Recursive calls for ancestors of
    // node to be deleted
    if (root->getDepartureTime() > k) {
        root->setLeftPtr(deleteNode(root->getLeftPtr(), k));
        return root;
    }
    else if (root->getDepartureTime() < k) {
        root->setRightPtr(deleteNode(root->getRightPtr(), k));
        return root;
    }
 
    // We reach here when root is the node
    // to be deleted.
 
    // If one of the children is empty
    if (root->getLeftPtr() == NULL) {
        BinaryTreeNode* temp = root->getRightPtr();
        delete root;
        return temp;
    }
    else if (root->getRightPtr() == NULL) {
        BinaryTreeNode* temp = root->getLeftPtr();
        delete root;
        return temp;
    }
 
    // If both children exist
    else {
 
        BinaryTreeNode* succParent = root;
 
        // Find successor
        BinaryTreeNode* succ = root->getRightPtr();
        while (succ->getLeftPtr() != NULL) {
            succParent = succ;
            succ = succ->getLeftPtr();
        }
        if (succParent != root)
            succParent->setLeftPtr(succ->getRightPtr());
        else
            succParent->setRightPtr(succ->getRightPtr());
 
        // Copy Successor Data to root
        root->setTripNodePtr(succ->getTripNodePtr())  ;
 
        delete succ;
        return root;
    }
}

};

class TravelDesk
{
public:
    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time)
    {
        // Implement this function to add a trip
        // Check if the vehicle already exists, if not, create a new one with the seating capacity
        Vehicle *vehicle = nullptr;

        int vflag = 0;
        int lflag = 0;
        for (int i = 0; i < vehicles.size(); i++)
        {
            if (vehicles[i]->getVehicleNumber() == vehicle_number)
            {
                vflag = 1;
                vehicle = vehicles[i];
                break;
            }
        }
        if (vflag == 0)
        {
            vehicle = new Vehicle(vehicle_number, seating_capacity);
            vehicles.push_back(vehicle);
        }

        // Create a new trip and add it to the appropriate objects

        // Create or retrieve the Location object and associated pick up location

        // Add the trip to the TransportService's BST
        Trip *new_trip = new Trip(vehicle, pick_up_location, drop_location, departure_time);
        vehicle->addTrip(new_trip);
        for (int i = 0; i < locations.size(); i++)
        {
            if (locations[i]->getName() == pick_up_location)
            {
                locations[i]->addTrip(new_trip);
                lflag = 1;
                break;
            }
        }
        if (lflag == 0)
        {
            Location *new_location = new Location(pick_up_location);
            new_location->addTrip(new_trip);
            locations.push_back(new_location);
        }
        Location *location_for_adding_service_ptr = getLocation(pick_up_location);
        TransportService *serviceptr = location_for_adding_service_ptr->getServicePtr(drop_location);
        serviceptr->addTrip(departure_time, new_trip);
    }

    std::vector<Trip *> showTrips(std::string pick_up_location, int after_time, int before_time)
    {
        std::vector<Trip *> result;
        for (int i = 0; i < vehicles.size(); i++)
        {
            std::vector<Trip *> trip_fetch = vehicles[i]->getTrips();
            for (int j = 0; j < trip_fetch.size(); j++)
            {
                if (trip_fetch[j]->getPickUpLocation() == pick_up_location && trip_fetch[j]->getDepartureTime() <= before_time && trip_fetch[j]->getDepartureTime() >= after_time)
                {
                    result.push_back(trip_fetch[j]);
                }
            }
        }
        return result;
    }
    std::vector<Trip *> showTripsbydestination(std::string pick_up_location, std::string destination, int after_time, int before_time)
    {
        // Implement this function to retrieve trips within a specified time range form pickup to droplocatin
        Location *retrieve_location = getLocation(pick_up_location);
        TransportService *service_ptr = retrieve_location->getServicePtr(destination);
        service_ptr->trips_within_specified_range(service_ptr->getBSTHead(), after_time, before_time);
        return service_ptr->trips;

    }

    Trip *bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time)
    {
        class TempTree : public BinarySearchTree
        {
        public:
            TempTree(BinaryTreeNode *root1)
            {
                root = root1;
            }
        };




        Location *retrieve_location = getLocation(pick_up_location);
        TransportService *service_ptr = retrieve_location->getServicePtr(drop_location);
        BinaryTreeNode *root_location = service_ptr->getBSTHead();
        TempTree *t = new TempTree(root_location);
        BinaryTreeNode *retrieve_tree_node = t->searchNodeWithKey(departure_time);
        if(retrieve_tree_node==nullptr)
        {
            return nullptr;
        }
        Trip *retrieve_trip = retrieve_tree_node->getTripNodePtr();
        int x = retrieve_trip->getBookedSeats();
        x++;
        retrieve_trip->setBookedSeats(x);
        if(x==retrieve_trip->getVehicle()->getSeatingCapacity())
        {
            t->deleteNode(root_location,retrieve_tree_node->getDepartureTime());

        }

        return retrieve_trip;
    }
    Location *getLocation(std::string location)
    {
        for (int i = 0; i < locations.size(); i++)
        {
            if (locations[i]->getName() == location)
            {
                return locations[i];
            }
        }
        return nullptr;
    }

private:
    std::vector<Vehicle *> vehicles;
    std::vector<Location *> locations;
};
