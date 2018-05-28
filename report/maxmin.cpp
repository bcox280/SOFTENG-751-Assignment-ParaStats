if (!(id % (i * 2)) && ((id + i) < size)) {
            local_minmax[id] = (local_minmax[id] > local_minmax[id+i]) ?
            local_minmax[id+i] : local_minmax[id];
} else if (!((id - 1) % (i * 2)) && ((id - 1 + i) < size)) {
            local_minmax[id] = (local_minmax[id] < local_minmax[id+i]) ?
            local_minmax[id+i] : local_minmax[id];
}
