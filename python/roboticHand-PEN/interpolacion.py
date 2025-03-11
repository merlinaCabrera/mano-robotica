def interpolar(minViejo, maxViejo, minNuevo, maxNuevo, actual):
    actual = round(actual)

    if actual < minNuevo:
        return minNuevo

    if actual > maxNuevo:
        return maxNuevo

    resultado = actual * maxNuevo / maxViejo

    return resultado
