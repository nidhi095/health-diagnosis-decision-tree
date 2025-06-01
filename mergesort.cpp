void mergeSort(vector<pair<string,int>>& arr, int l, int r) {
        if (l >= r) return;
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }

    void merge(vector<pair<string,int>>& arr, int l, int m, int r) {
        vector<pair<string,int>> temp(r-l+1);
        int i=l, j=m+1, k=0;
        while(i<=m && j<=r) {
            if(arr[i].second > arr[j].second)
                temp[k++] = arr[i++];
            else
                temp[k++] = arr[j++];
        }
        while(i<=m) temp[k++] = arr[i++];
        while(j<=r) temp[k++] = arr[j++];
        for(int x=0;x<temp.size();x++) arr[l+x] = temp[x];
    }
};
