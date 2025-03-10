/*
 * QEMU Generic PCI Express Bridge Emulation
 *
 * Copyright (C) 2015 Alexander Graf <agraf@suse.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>
 */

#ifndef HW_GPEX_H
#define HW_GPEX_H

#include "exec/hwaddr.h"
#include "hw/sysbus.h"
#include "hw/pci/pci_device.h"
#include "hw/pci/pcie_host.h"
#include "qom/object.h"

#define TYPE_GPEX_HOST "gpex-pcihost"
OBJECT_DECLARE_SIMPLE_TYPE(GPEXHost, GPEX_HOST)

#define TYPE_GPEX_ROOT_DEVICE "gpex-root"
OBJECT_DECLARE_SIMPLE_TYPE(GPEXRootState, GPEX_ROOT_DEVICE)

struct GPEXRootState {
    /*< private >*/
    PCIDevice parent_obj;
    /*< public >*/
};

struct GPEXHost {
    /*< private >*/
    PCIExpressHost parent_obj;
    /*< public >*/

    GPEXRootState gpex_root;

    MemoryRegion io_ioport;
    MemoryRegion io_mmio;
    MemoryRegion io_ioport_window;
    MemoryRegion io_mmio_window;
    uint32_t nr_irqs;
    qemu_irq *irq;
    int *irq_num;

    bool allow_unmapped_accesses;
};

struct GPEXConfig {
    MemMapEntry ecam;
    MemMapEntry mmio32;
    MemMapEntry mmio64;
    MemMapEntry pio;
    int         irq;
    PCIBus      *bus;
};

int gpex_set_irq_num(GPEXHost *s, int index, int gsi);

void acpi_dsdt_add_gpex(Aml *scope, struct GPEXConfig *cfg);

#endif /* HW_GPEX_H */
