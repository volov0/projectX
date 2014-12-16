/**
 * @file rotate.h
 * @author volovo
 * @date 16.12.2014
 * @brief implementace rotace v poli
 */

#ifndef ROTATE_H
#define ROTATE_H

/**
 * Function rotate
 * ---------------
 * @param front - zacatek pole
 * @param middle - ukazetel do pole, ktery urcuje rotovani
 * @param end - ukazatel na konec pole
 * @detail Funkce posune uvodni cast pole (od front az k middle)
 * na konec pole. Tzn cast od middle do end se posune na zacatek
 */
void rotate(void *front, void *middle, void *end);

#endif  /* ROTATE_H */
