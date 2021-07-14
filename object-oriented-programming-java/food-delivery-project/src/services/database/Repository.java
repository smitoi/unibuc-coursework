package services.database;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class Repository<K, T> {
    protected Map<K, List<T>> repoList;

    public T addOne(K key, T obj) {
        if (!repoList.containsKey(key)) {
            repoList.put(key, new ArrayList<>());
        }
        repoList.get(key).add(obj);
        return obj;
    }

    public T getOne(K key, int index) {
        return repoList.get(key).get(index);
    }

    public List<T> getAll() {
        List<List<T>> repoListOfLists = new ArrayList<>(repoList.values());
        List<T> result = new ArrayList<>();
        repoListOfLists.forEach(result::addAll);
        return result;
    }

    public List<T> getAll(K key) {
        return repoList.get(key);
    }

    public void delete(K key, int index) {
        repoList.get(key).remove(index);
    }

    public void remove(K key, T obj) { repoList.get(key).remove(obj); }
}
