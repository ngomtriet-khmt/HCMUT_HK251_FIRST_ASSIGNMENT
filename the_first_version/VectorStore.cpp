#include "VectorStore.h"

// ----------------- ArrayList Implementation -----------------

template <class T>
void ArrayList<T>::ensureCapacity(int cap) {
    if (cap > capacity) {
        int newCapacity = static_cast<int>(capacity * 1.5);
        if (newCapacity < cap) {
            newCapacity = cap;
        }
        T* newData = new T[newCapacity];
        for (int i = 0; i < count; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
}

template <class T>
ArrayList<T>::ArrayList(int initCapacity) {
    capacity = initCapacity;
    count = 0;
    data = new T[capacity];
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T>& other) {
    capacity = other.capacity;
    count = other.count;
    data = new T[capacity];
    for (int i = 0; i < count; i++) {
        data[i] = other.data[i];
    }
}   

template <class T>
ArrayList<T>::~ArrayList() {
    delete[] data;
}

template <class T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other) {
    if (this != &other) {
        delete[] data;
        capacity = other.capacity;
        count = other.count;
        data = new T[capacity];
        for (int i = 0; i < count; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <class T>
void ArrayList<T>::add(T e) {
    ensureCapacity(count + 1);
    data[count] = e;
    count++;
}

template <class T>
void ArrayList<T>::add(int index, T e) {
    if (index < 0 || index > count) {
        throw out_of_range("Index is invalid!");
    }
    ensureCapacity(count + 1);
    for (int i = count; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = e;
    count++;
}

template <class T>
T ArrayList<T>::removeAt(int index) {
    if (index < 0 || index >= count) {
        throw out_of_range("Index is invalid!");
    }
    T removedItem = data[index];
    for (int i = index; i < count - 1; i++) {
        data[i] = data[i + 1];
    }
    count--;
    return removedItem;
}

template <class T>
bool ArrayList<T>::empty() const {
    return count == 0;
}

template <class T>
int ArrayList<T>::size() const {
    return count;
}

template <class T>
void ArrayList<T>::clear() {
    delete[] data;
    count = 0;
    capacity = 10;
    data = new T[capacity];
}

template <class T>
T& ArrayList<T>::get(int index) {
    if (index < 0 || index >= count) {
        throw out_of_range("Index is invalid!");
    }
    return data[index];
}

template <class T>
const T& ArrayList<T>::get(int index) const {
    if (index < 0 || index >= count) {
        throw out_of_range("Index is invalid!");
    }
    return data[index];
}

template <class T>
void ArrayList<T>::set(int index, T e) {
    if (index < 0 || index >= count) {
        throw out_of_range("Index is invalid!");
    }
    data[index] = e;
}

template <class T>
int ArrayList<T>::indexOf(T item) const {
    for (int i = 0; i < count; i++) {
        if (data[i] == item) {
            return i;
        }
    }
    return -1;
}

template <class T>
bool ArrayList<T>::contains(T item) const {
    return indexOf(item) != -1;
}

template <class T>
string ArrayList<T>::toString(string (*item2str)(T&)) const {
    stringstream ss;
    ss << "[";
    for (int i = 0; i < count; i++) {
        if (item2str) {
            ss << item2str(data[i]);
        } else {
            ss << data[i];
        }
        if (i < count - 1) {
            ss << ", ";
        }
    }
    ss << "]";
    return ss.str();
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::begin() {
    return Iterator(this, 0);
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::end() {
    return Iterator(this, count);
}

// ----------------- Iterator of ArrayList Implementation -----------------
template <class T>
ArrayList<T>::Iterator::Iterator(ArrayList<T>* pList, int index) {
    this->pList = pList;
    if (pList == nullptr || index < 0 || index > pList->count) {
        throw out_of_range("Index is invalid!");
    }
    this->cursor = index;
}

template <class T>
typename ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator=(const Iterator& other) {
    this->pList = other.pList;
    this->cursor = other.cursor;
    return *this;
}

template <class T>
T& ArrayList<T>::Iterator::operator*() {
    if (cursor < 0 || cursor >= pList->count) {
        throw out_of_range("Iterator is out of range!");
    }
    return pList->data[cursor];
}

template <class T>
bool ArrayList<T>::Iterator::operator!=(const Iterator& other) const {
    return pList != other.pList || cursor != other.cursor;
}

template <class T>
typename ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator++() {
    if (cursor >= pList->count) {
        throw out_of_range("Iterator cannot advance past end!");
    }
    cursor++;
    return *this;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    if (cursor >= pList->count) {
        throw out_of_range("Iterator cannot advance past end!");
    }
    cursor++;
    return temp;
}

template <class T>
typename ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator--() {
    if (cursor <= 0) {
        throw out_of_range("Iterator cannot move before begin!");
    }
    cursor--;
    return *this;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::Iterator::operator--(int) {
    Iterator temp = *this;
    if (cursor <= 0) {
        throw out_of_range("Iterator cannot move before begin!");
    }
    cursor--;
    return temp;
}

// ----------------- SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::SinglyLinkedList() {
    head = nullptr;
    tail = nullptr;
    count = 0;
}   

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    clear();
}   

template <class T>
void SinglyLinkedList<T>::add(T e) {
    Node* newNode = new Node(e);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    count++;
}

template <class T>
void SinglyLinkedList<T>::add(int index, T e) {
    if (index < 0 || index > count) {
        throw out_of_range("Index is invalid!");
    }
    
    if (index == 0) {
        Node* newNode = new Node(e, head);
        head = newNode;
        if (tail == nullptr) {
            tail = newNode;
        }
    } else if (index == count) {
        add(e);
        return;
    } else {
        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        Node* newNode = new Node(e, current->next);
        current->next = newNode;
    }
    count++;
}

template <class T>
T SinglyLinkedList<T>::removeAt(int index) {
    if (index < 0 || index >= count) {
        throw out_of_range("Index is invalid!");
    }
    
    T data;
    if (index == 0) {
        Node* temp = head;
        data = temp->data;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp;
    } else {
        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        Node* temp = current->next;
        data = temp->data;
        current->next = temp->next;
        if (temp == tail) {
            tail = current;
        }
        delete temp;
    }
    count--;
    return data;
}

template <class T>
bool SinglyLinkedList<T>::removeItem(T item) {
    if (head == nullptr) return false;
    
    if (head->data == item) {
        Node* temp = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp;
        count--;
        return true;
    }
    
    Node* current = head;
    while (current->next != nullptr && current->next->data != item) {
        current = current->next;
    }
    
    if (current->next != nullptr) {
        Node* temp = current->next;
        current->next = temp->next;
        if (temp == tail) {
            tail = current;
        }
        delete temp;
        count--;
        return true;
    }
    return false;
}

template <class T>
bool SinglyLinkedList<T>::empty() const {
    return count == 0;
}

template <class T>
int SinglyLinkedList<T>::size() const {
    return count;
}

template <class T>
void SinglyLinkedList<T>::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    count = 0;
}

template <class T>
T& SinglyLinkedList<T>::get(int index) {
    if (index < 0 || index >= count) {
        throw out_of_range("Index is invalid!");
    }
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template <class T>
const T& SinglyLinkedList<T>::get(int index) const {
    if (index < 0 || index >= count) {
        throw out_of_range("Index is invalid!");
    }
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template <class T>
int SinglyLinkedList<T>::indexOf(T item) const {
    Node* current = head;
    for (int i = 0; i < count; i++) {
        if (current->data == item) {
            return i;
        }
        current = current->next;
    }
    return -1;
}

template <class T>
bool SinglyLinkedList<T>::contains(T item) const {
    return indexOf(item) != -1;
}

template <class T>
string SinglyLinkedList<T>::toString(string (*item2str)(T&)) const {
    stringstream ss;
    Node* current = head;
    bool first = true;
    while (current != nullptr) {
        if (!first) {
            ss << "->";
        }
        ss << "[";
        if (item2str) {
            ss << item2str(current->data);
        } else {
            ss << current->data;
        }
        ss << "]";
        first = false;
        current = current->next;
    }
    return ss.str();
}

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::begin() {
    return Iterator(head);
}

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::end() {
    return Iterator(nullptr);
}

// ----------------- Iterator of SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::Iterator::Iterator(Node* node) {
    current = node;
}   

template <class T>
typename SinglyLinkedList<T>::Iterator& SinglyLinkedList<T>::Iterator::operator=(const Iterator& other) {
    current = other.current;
    return *this;
}

template <class T>
T& SinglyLinkedList<T>::Iterator::operator*() {
    if (current == nullptr) {
        throw out_of_range("Iterator is out of range!");
    }
    return current->data;
}

template <class T>
bool SinglyLinkedList<T>::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

template <class T>
typename SinglyLinkedList<T>::Iterator& SinglyLinkedList<T>::Iterator::operator++() {
    if (current == nullptr) {
        throw out_of_range("Iterator cannot advance past end!");
    }
    current = current->next;
    return *this;
}

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    if (current == nullptr) {
        throw out_of_range("Iterator cannot advance past end!");
    }
    current = current->next;
    return temp;
}

// ----------------- VectorStore Implementation -----------------

VectorStore::VectorRecord::VectorRecord(int id, const string& rawText, SinglyLinkedList<float>* vector) {
    this->id = id;
    this->rawText = rawText;
    this->rawLength = rawText.length();
    this->vector = vector;
}

VectorStore::VectorStore(int dimension, EmbedFn embeddingFunction) {
    this->dimension = dimension;
    this->count = 0;
    this->embeddingFunction = embeddingFunction;
}

VectorStore::~VectorStore() {
    clear();
}

int VectorStore::size() const {
    return count;
}

bool VectorStore::empty() const {
    return count == 0;
}

void VectorStore::clear() {
    for (int i = 0; i < records.size(); i++) {
        delete records.get(i)->vector;
        delete records.get(i);
    }
    records.clear();
    count = 0;
}

SinglyLinkedList<float>* VectorStore::preprocessing(string rawText) {
    if (embeddingFunction == nullptr) {
        return new SinglyLinkedList<float>();
    }
    
    SinglyLinkedList<float>* vector = embeddingFunction(rawText);
    
    // Adjust vector dimension
    int currentSize = vector->size();
    if (currentSize > dimension) {
        // Remove excess elements from the end
        while (vector->size() > dimension) {
            vector->removeAt(vector->size() - 1);
        }
    } else if (currentSize < dimension) {
        // Add zeros to the end
        while (vector->size() < dimension) {
            vector->add(0.0f);
        }
    }
    
    return vector;
}

void VectorStore::addText(string rawText) {
    SinglyLinkedList<float>* vector = preprocessing(rawText);
    VectorRecord* record = new VectorRecord(count, rawText, vector);
    records.add(record);
    count++;
}

SinglyLinkedList<float>& VectorStore::getVector(int index) {
    if (index < 0 || index >= count) {
        throw out_of_range("Index is invalid!");
    }
    return *(records.get(index)->vector);
}

string VectorStore::getRawText(int index) const {
    if (index < 0 || index >= count) {
        throw out_of_range("Index is invalid!");
    }
    return records.get(index)->rawText;
}

int VectorStore::getId(int index) const {
    if (index < 0 || index >= count) {
        throw out_of_range("Index is invalid!");
    }
    return records.get(index)->id;
}

bool VectorStore::removeAt(int index) {
    if (index < 0 || index >= count) {
        throw out_of_range("Index is invalid!");
    }
    
    VectorRecord* record = records.get(index);
    delete record->vector;
    delete record;
    records.removeAt(index);
    count--;
    return true;
}

bool VectorStore::updateText(int index, string newRawText) {
    if (index < 0 || index >= count) {
        throw out_of_range("Index is invalid!");
    }
    
    VectorRecord* record = records.get(index);
    delete record->vector;
    
    record->rawText = newRawText;
    record->rawLength = newRawText.length();
    record->vector = preprocessing(newRawText);
    
    return true;
}

void VectorStore::setEmbeddingFunction(EmbedFn newEmbeddingFunction) {
    embeddingFunction = newEmbeddingFunction;
}

void VectorStore::forEach(void (*action)(SinglyLinkedList<float>&, int, string&)) {
    for (int i = 0; i < count; i++) {
        VectorRecord* record = records.get(i);
        action(*(record->vector), record->id, record->rawText);
    }
}

double VectorStore::cosineSimilarity(const SinglyLinkedList<float>& v1, const SinglyLinkedList<float>& v2) const {
    if (v1.size() != v2.size()) return 0.0;
    
    double dotProduct = 0.0;
    double norm1 = 0.0;
    double norm2 = 0.0;
    
    SinglyLinkedList<float>::Iterator it1 = const_cast<SinglyLinkedList<float>&>(v1).begin();
    SinglyLinkedList<float>::Iterator it2 = const_cast<SinglyLinkedList<float>&>(v2).begin();
    
    while (it1 != const_cast<SinglyLinkedList<float>&>(v1).end() && 
           it2 != const_cast<SinglyLinkedList<float>&>(v2).end()) {
        float val1 = *it1;
        float val2 = *it2;
        dotProduct += val1 * val2;
        norm1 += val1 * val1;
        norm2 += val2 * val2;
        ++it1;
        ++it2;
    }
    
    if (norm1 == 0.0 || norm2 == 0.0) return 0.0;
    
    return dotProduct / (sqrt(norm1) * sqrt(norm2));
}

double VectorStore::l1Distance(const SinglyLinkedList<float>& v1, const SinglyLinkedList<float>& v2) const {
    if (v1.size() != v2.size()) return 0.0;
    
    double distance = 0.0;
    
    SinglyLinkedList<float>::Iterator it1 = const_cast<SinglyLinkedList<float>&>(v1).begin();
    SinglyLinkedList<float>::Iterator it2 = const_cast<SinglyLinkedList<float>&>(v2).begin();
    
    while (it1 != const_cast<SinglyLinkedList<float>&>(v1).end() && 
           it2 != const_cast<SinglyLinkedList<float>&>(v2).end()) {
        float val1 = *it1;
        float val2 = *it2;
        distance += abs(val1 - val2);
        ++it1;
        ++it2;
    }
    
    return distance;
}

double VectorStore::l2Distance(const SinglyLinkedList<float>& v1, const SinglyLinkedList<float>& v2) const {
    if (v1.size() != v2.size()) return 0.0;
    
    double distance = 0.0;
    
    SinglyLinkedList<float>::Iterator it1 = const_cast<SinglyLinkedList<float>&>(v1).begin();
    SinglyLinkedList<float>::Iterator it2 = const_cast<SinglyLinkedList<float>&>(v2).begin();
    
    while (it1 != const_cast<SinglyLinkedList<float>&>(v1).end() && 
           it2 != const_cast<SinglyLinkedList<float>&>(v2).end()) {
        float val1 = *it1;
        float val2 = *it2;
        double diff = val1 - val2;
        distance += diff * diff;
        ++it1;
        ++it2;
    }
    
    return sqrt(distance);
}

int VectorStore::findNearest(const SinglyLinkedList<float>& query, const string& metric) const {
    if (count == 0) return -1;
    
    if (metric != "cosine" && metric != "euclidean" && metric != "manhattan") {
        throw invalid_metric();
    }
    
    int bestIndex = 0;
    double bestScore = 0.0;
    bool first = true;
    
    for (int i = 0; i < count; i++) {
        double score = 0.0;
        const SinglyLinkedList<float>& currentVector = *(records.get(i)->vector);
        
        if (metric == "cosine") {
            score = cosineSimilarity(query, currentVector);
            if (first || score > bestScore) {
                bestScore = score;
                bestIndex = i;
            }
        } else if (metric == "euclidean") {
            score = l2Distance(query, currentVector);
            if (first || score < bestScore) {
                bestScore = score;
                bestIndex = i;
            }
        } else if (metric == "manhattan") {
            score = l1Distance(query, currentVector);
            if (first || score < bestScore) {
                bestScore = score;
                bestIndex = i;
            }
        }
        first = false;
    }
    
    return bestIndex;
}

int* VectorStore::topKNearest(const SinglyLinkedList<float>& query, int k, const string& metric) const {
    if (metric != "cosine" && metric != "euclidean" && metric != "manhattan") {
        throw invalid_metric();
    }
    
    if (k <= 0 || k > count) {
        throw invalid_k_value();
    }
    
    // Create array to store results
    int* results = new int[k];
    double* scores = new double[k];
    
    // Initialize with first k elements
    for (int i = 0; i < k; i++) {
        results[i] = i;
        const SinglyLinkedList<float>& currentVector = *(records.get(i)->vector);
        
        if (metric == "cosine") {
            scores[i] = cosineSimilarity(query, currentVector);
        } else if (metric == "euclidean") {
            scores[i] = l2Distance(query, currentVector);
        } else if (metric == "manhattan") {
            scores[i] = l1Distance(query, currentVector);
        }
    }
    
    // Sort initial k elements
    for (int i = 0; i < k - 1; i++) {
        for (int j = i + 1; j < k; j++) {
            bool shouldSwap = false;
            if (metric == "cosine") {
                shouldSwap = scores[i] < scores[j];
            } else {
                shouldSwap = scores[i] > scores[j];
            }
            
            if (shouldSwap) {
                swap(scores[i], scores[j]);
                swap(results[i], results[j]);
            }
        }
    }
    
    // Process remaining elements
    for (int i = k; i < count; i++) {
        const SinglyLinkedList<float>& currentVector = *(records.get(i)->vector);
        double currentScore = 0.0;
        
        if (metric == "cosine") {
            currentScore = cosineSimilarity(query, currentVector);
        } else if (metric == "euclidean") {
            currentScore = l2Distance(query, currentVector);
        } else if (metric == "manhattan") {
            currentScore = l1Distance(query, currentVector);
        }
        
        // Check if current element should be in top k
        bool shouldInclude = false;
        if (metric == "cosine") {
            shouldInclude = currentScore > scores[k-1];
        } else {
            shouldInclude = currentScore < scores[k-1];
        }
        
        if (shouldInclude) {
            // Replace worst element
            scores[k-1] = currentScore;
            results[k-1] = i;
            
            // Re-sort to maintain order
            for (int j = k-1; j > 0; j--) {
                bool shouldSwap = false;
                if (metric == "cosine") {
                    shouldSwap = scores[j] > scores[j-1];
                } else {
                    shouldSwap = scores[j] < scores[j-1];
                }
                
                if (shouldSwap) {
                    swap(scores[j], scores[j-1]);
                    swap(results[j], results[j-1]);
                } else {
                    break;
                }
            }
        }
    }
    
    delete[] scores;
    return results;
}


// Explicit template instantiation for char, string, int, double, float, and Point

template class ArrayList<char>;
template class ArrayList<string>;
template class ArrayList<int>;
template class ArrayList<double>;
template class ArrayList<float>;
template class ArrayList<Point>;

template class SinglyLinkedList<char>;
template class SinglyLinkedList<string>;
template class SinglyLinkedList<int>;
template class SinglyLinkedList<double>;
template class SinglyLinkedList<float>;
template class SinglyLinkedList<Point>;
