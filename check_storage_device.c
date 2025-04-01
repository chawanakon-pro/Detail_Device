#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>
#include <mntent.h>

//print_size will select the type GB, MB, KB
void print_size(unsigned long size) {
    if (size >= 1024L * 1024 * 1024) {
        printf("%.2f GB", size / (1024.0 * 1024 * 1024));
    } else if (size >= 1024L * 1024) {
        printf("%.2f MB", size / (1024.0 * 1024));
    } else if (size >= 1024L) {
        printf("%.2f KB", size / 1024.0);
    } else {
        printf("%lu bytes", size);
    }
}

void print_storage_info(const char *path) {
    struct statvfs stat;
    if (statvfs(path, &stat) != 0) {
        perror("statvfs failed");
        return;
    }
    
    unsigned long total_size = stat.f_blocks * stat.f_frsize;
    unsigned long free_size = stat.f_bfree * stat.f_frsize;
    unsigned long used_size = total_size - free_size;
    double total_percentage = ((double)total_size/ (double)total_size) * 100.0;
    double free_percentage = ((double)free_size / (double)total_size) * 100.0;
    
    printf("-------------------------------\n");
    printf("Device Path: %s\n", path);
    printf("Total Capacity: ");
    print_size(total_size);
    printf(" (%.2f%%)\n", total_percentage);
    printf("Unused Capacity: ");
    print_size(free_size);
    printf(" (%.2f%%)\n", free_percentage);
    
}

int main() {
    FILE *fp = setmntent("/etc/mtab", "r");
    if (!fp) {
        perror("setmntent failed");
        return 1;
    }
    
    struct mntent *entry;
    while ((entry = getmntent(fp)) != NULL) {
        print_storage_info(entry->mnt_dir);
    }
    
    endmntent(fp);
    return 0;
}
